package domain

type Student struct {
	ID          int
	Name        string
	Surname     string
	Patronymic  string
	GroupNumber string
}

type StudentMarks struct {
	Student *Student
	Marks   map[string]int
}
