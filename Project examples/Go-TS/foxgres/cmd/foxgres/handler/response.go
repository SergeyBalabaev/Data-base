package handler

import "foxgres/internal/domain"

type AccessLevel struct {
	AccessLevel int `json:"access_level,omitempty"`
} // @name AccessLevel

type ResponseErr struct {
	Message string `json:"message,omitempty"`
} // @name ResponseErr

type Student struct {
	Name        string `json:"name,omitempty"`
	Surname     string `json:"surname,omitempty"`
	Patronymic  string `json:"patronymic,omitempty"`
	GroupNumber string `json:"group_number,omitempty"`
} // @name Student

type Marks struct {
	Student Student        `json:"student"`
	Marks   map[string]int `json:"marks,omitempty"`
} // @name Marks

func domainMarksToResponse(m *domain.StudentMarks) Marks {
	return Marks{
		Student: Student{
			Name:        m.Student.Name,
			Surname:     m.Student.Surname,
			Patronymic:  m.Student.Patronymic,
			GroupNumber: m.Student.GroupNumber,
		},
		Marks: m.Marks,
	}
}
