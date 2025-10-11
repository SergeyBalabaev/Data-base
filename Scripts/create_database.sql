--DROP DATABASE ORIOKS;
--CREATE DATABASE ORIOKS;
DROP TABLE IF EXISTS Students CASCADE;
DROP TABLE IF EXISTS Structural_units CASCADE;
DROP TABLE IF EXISTS Students_groups CASCADE;
DROP TABLE IF EXISTS Student_ids CASCADE;
DROP TABLE IF EXISTS Professors CASCADE;
DROP TABLE IF EXISTS Fields CASCADE;
DROP TABLE IF EXISTS Employments CASCADE;
DROP TABLE IF EXISTS Field_comprehensions CASCADE;


CREATE TABLE Structural_units(
    structural_unit_id SERIAL PRIMARY KEY,
    full_title TEXT NOT NULL,
    abbreviated_title VARCHAR(20) NULL,
    head_of_the_unit VARCHAR(40) NOT NULL,
	phone_number VARCHAR(5) CHECK (phone_number ~* '^[0-9]{2}-[0-9]{2}$')
);


CREATE TABLE Students_groups(
    students_group_number VARCHAR(7) PRIMARY KEY CHECK (students_group_number ~* '^[А-Яа-я]+-[МВ0-9]+$'),
    enrolment_status VARCHAR(12) NOT NULL CHECK (enrolment_status = ANY ('{Очная, Заочная, Очно-заочная}'::VARCHAR[])),
    structural_unit_id INTEGER NOT NULL REFERENCES Structural_units(structural_unit_id) ON DELETE CASCADE
);

CREATE TABLE Students(
    student_id INTEGER NOT NULL,
    last_name VARCHAR(30) NOT NULL,
    first_name VARCHAR(30) NOT NULL,
    patronymic VARCHAR(30) NULL,
    students_group_number VARCHAR(7) NOT NULL,
    birthday DATE NOT NULL,
    email VARCHAR(30) UNIQUE,
    PRIMARY KEY(student_id),
    CONSTRAINT Students_group_key
        FOREIGN KEY(students_group_number) 
            REFERENCES Students_groups(students_group_number)
            ON DELETE CASCADE,
    CONSTRAINT email_cheak 
        CHECK (email ~* '^[A-Za-z0-9._+%-]+@[A-Za-z0-9.-]+[.][A-Za-z]+$')
);


CREATE TABLE Student_ids(
    student_id INTEGER NOT NULL,
    issue_date DATE NOT NULL DEFAULT CURRENT_DATE,
    expiration_date DATE NOT NULL DEFAULT (CURRENT_DATE + interval '4 year'),
	PRIMARY KEY(student_id),
	FOREIGN KEY(student_id) 
		REFERENCES Students(student_id) 
		ON DELETE CASCADE
);

CREATE TABLE Professors(
    professor_id INTEGER NOT NULL,
    last_name VARCHAR(30) NOT NULL,
    first_name VARCHAR(30) NOT NULL,
    patronymic VARCHAR(30) NULL,
    degree VARCHAR(15) NULL CHECK (degree ~* '^[кКдД].+[а-яА-Я].+[н].+$'),
    academic_title VARCHAR(40) NULL,
    current_position VARCHAR(40) NOT NULL,
    experience INTEGER NOT NULL,
	salary MONEY,
	PRIMARY KEY(professor_id)
);

CREATE TABLE Fields(
    field_id UUID NOT NULL,
    field_name VARCHAR(100) NOT NULL,
    structural_unit_id INTEGER NOT NULL REFERENCES Structural_units(structural_unit_id) ON DELETE CASCADE,
    professor_id INTEGER NOT NULL REFERENCES Professors(professor_id) ON DELETE CASCADE,
    ZET INTEGER NOT NULL,
    semester INTEGER NOT NULL,
	PRIMARY KEY(field_id)
);


CREATE TABLE Employments(
    structural_unit_id INTEGER NOT NULL REFERENCES Structural_units ON DELETE CASCADE,
    professor_id INTEGER NOT NULL REFERENCES Professors ON DELETE CASCADE,
    contract_number INTEGER NOT NULL,
	wage_rate NUMERIC(3,2) NOT NULL,
	PRIMARY KEY(
        structural_unit_id, 
		professor_id
    )
);

CREATE TABLE Field_comprehensions(
    student_id INTEGER NOT NULL REFERENCES Students(student_id) ON DELETE CASCADE,
    field UUID NOT NULL REFERENCES Fields(field_id) ON DELETE CASCADE,
    mark INTEGER CHECK (mark >=2 AND mark <=5),
	PRIMARY KEY(student_id, field)
);

