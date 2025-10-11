package storage

import (
	"context"
	"strings"

	"github.com/jackc/pgx/v5"
)

type FieldStorage interface {
	GetSubjectIDs(ctx context.Context, studentID int) (map[string]int, error)
	GetSubjectNames(ctx context.Context, fieldIDs []string) (map[string]string, error)
}

type fieldStorage struct {
	conn *pgx.Conn
}

func NewFieldStorage(conn *pgx.Conn) FieldStorage {
	return &fieldStorage{
		conn: conn,
	}
}

const getSubjectIDsQuery = `SELECT field, mark FROM field_comprehension WHERE student_id=$1`

func (s *fieldStorage) GetSubjectIDs(ctx context.Context, studentID int) (map[string]int, error) {
	marks := make(map[string]int, 0)
	rows, err := s.conn.Query(ctx, getSubjectIDsQuery, studentID)
	if err != nil {
		return nil, err
	}
	var id string
	var mark int
	for rows.Next() {
		err = rows.Scan(
			&id,
			&mark)
		if err != nil {
			return nil, err
		}
		marks[id] = mark
	}
	return marks, nil
}

func getSubjectNamesQuery(fieldIDs []string) string {
	var buf strings.Builder

	for i, f := range fieldIDs {
		if f == "" {
			continue
		}
		buf.WriteString(`'`)
		buf.WriteString(f)
		buf.WriteString(`'`)
		if i != len(fieldIDs)-1 {
			buf.WriteString(", ")
		}
	}
	return `SELECT field_id, field_name FROM field WHERE field_id IN` + `(` + buf.String() + `)`
}

func (s *fieldStorage) GetSubjectNames(ctx context.Context, fieldIDs []string) (map[string]string, error) {
	names := make(map[string]string, 0)
	rows, err := s.conn.Query(ctx, getSubjectNamesQuery(fieldIDs))
	if err != nil {
		return nil, err
	}
	var id, name string
	for rows.Next() {
		err = rows.Scan(
			&id,
			&name)
		if err != nil {
			return nil, err
		}
		names[id] = name
	}
	return names, nil
}
