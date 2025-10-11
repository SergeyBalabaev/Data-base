package storage

import (
	"context"

	"github.com/jackc/pgx/v5"

	"foxgres/internal/domain"
)

type StudentStorage interface {
	FindStudent(ctx context.Context, studentID int) (*domain.Student, error)
}

type studentStorage struct {
	conn *pgx.Conn
}

func NewStudentStorage(conn *pgx.Conn) StudentStorage {
	return &studentStorage{
		conn: conn,
	}
}

const findStudentQuery = `SELECT student_id, surname, name, patronymic, students_group_number FROM student WHERE student_id=$1`

func (s *studentStorage) FindStudent(ctx context.Context, studentID int) (*domain.Student, error) {
	row := s.conn.QueryRow(ctx, findStudentQuery, studentID)
	student := &domain.Student{}
	err := row.Scan(
		&student.ID,
		&student.Name,
		&student.Surname,
		&student.Patronymic,
		&student.GroupNumber)
	if err != nil {
		return &domain.Student{}, err
	}
	return student, nil
}
