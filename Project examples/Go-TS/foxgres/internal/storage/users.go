package storage

import (
	"context"

	"github.com/jackc/pgx/v5"
)

const (
	findUserQuery = `SELECT acess_level FROM users WHERE login=$1 AND password=$2;`
)

type UserStorage interface {
	FindUser(ctx context.Context, login int, pass string) (int, error)
}

type userStorage struct {
	conn *pgx.Conn
}

func NewUserStorage(conn *pgx.Conn) UserStorage {
	return &userStorage{
		conn: conn,
	}
}

func (s *userStorage) FindUser(ctx context.Context, login int, pass string) (int, error) {
	row := s.conn.QueryRow(ctx, findUserQuery, login, pass)
	var level int
	err := row.Scan(&level)
	if err != nil {
		return 0, err
	}
	return level, nil
}
