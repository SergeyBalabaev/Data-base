package service

import (
	"context"

	"foxgres/internal/domain"
	"foxgres/internal/storage"
)

type Service interface {
	FindUser(ctx context.Context, login int, pass string) (int, error)
	GetStudentMarks(ctx context.Context, studentID int) (*domain.StudentMarks, error)
}

type service struct {
	userStorage    storage.UserStorage
	fieldStorage   storage.FieldStorage
	studentStorage storage.StudentStorage
}

func NewService(us storage.UserStorage, fs storage.FieldStorage, ss storage.StudentStorage) Service {
	return &service{
		userStorage:    us,
		fieldStorage:   fs,
		studentStorage: ss,
	}
}

func (s *service) FindUser(ctx context.Context, login int, pass string) (int, error) {
	return s.userStorage.FindUser(ctx, login, pass)
}

func (s *service) GetStudentMarks(ctx context.Context, studentID int) (*domain.StudentMarks, error) {
	studentMarks := &domain.StudentMarks{
		Student: &domain.Student{},
		Marks:   make(map[string]int, 0),
	}
	student, err := s.studentStorage.FindStudent(ctx, studentID)
	if err != nil {
		return nil, err
	}

	subIDs, err := s.fieldStorage.GetSubjectIDs(ctx, studentID)
	if err != nil {
		return nil, err
	}

	ids := make([]string, 0, len(subIDs))
	for id := range subIDs {
		ids = append(ids, id)
	}

	subNames, err := s.fieldStorage.GetSubjectNames(ctx, ids)
	for id, mark := range subIDs {
		studentMarks.Marks[subNames[id]] = mark
	}

	studentMarks.Student = student

	return studentMarks, nil
}
