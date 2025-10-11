--DROP DATABASE ORIOKS;
--CREATE DATABASE ORIOKS;
DROP TABLE IF EXISTS Student CASCADE;
DROP TABLE IF EXISTS Structural_unit CASCADE;
DROP TABLE IF EXISTS Students_group;
DROP TABLE IF EXISTS Student_ID;
DROP TABLE IF EXISTS Professor CASCADE;
DROP TABLE IF EXISTS Field CASCADE;
DROP TABLE IF EXISTS Employment;
DROP TABLE IF EXISTS Field_comprehension;
DROP TABLE IF EXISTS Users;
DROP TABLE IF EXISTS debtor_students;

CREATE TABLE Structural_unit(
                                structural_unit_id SERIAL PRIMARY KEY,
                                unit_type VARCHAR(64) NOT NULL CHECK (unit_type = ANY ('{Кафедра, Институт}'::VARCHAR[])),
                                full_title TEXT NOT NULL,
                                abbreviated_title VARCHAR(20) NULL,
                                head_of_the_unit VARCHAR(40) NOT NULL
);

CREATE TABLE Students_group(
    students_group_number VARCHAR(7) PRIMARY KEY CHECK (students_group_number ~* '^[А-Яа-я]+-[МВ0-9]+$'),
    enrolment_status VARCHAR(12) NOT NULL CHECK (enrolment_status = ANY ('{Очная, Заочная, Очно-заочная}'::VARCHAR[])),
    structural_unit_number INTEGER NOT NULL REFERENCES structural_unit(structural_unit_id)
);

CREATE TABLE Student(
                        student_id INTEGER NOT NULL,
                        surname VARCHAR(30) NOT NULL,
                        name VARCHAR(30) NOT NULL,
                        patronymic VARCHAR(30) NULL,
                        students_group_number VARCHAR(7) NOT NULL,
                        birthday DATE NOT NULL,
                        email VARCHAR(30) UNIQUE,
                        PRIMARY KEY(student_id),
                        CONSTRAINT Students_group_key
                            FOREIGN KEY(students_group_number)
                                REFERENCES Students_group(students_group_number)
                                ON DELETE CASCADE,
                        CONSTRAINT email_cheak
                            CHECK (email ~* '^[A-Za-z0-9._+%-]+@[A-Za-z0-9.-]+[.][A-Za-z]+$')
    );


CREATE TABLE Student_id(
                           student_id INTEGER NOT NULL,
                           issue_date DATE NOT NULL DEFAULT CURRENT_DATE,
                           expiration_date DATE NOT NULL DEFAULT (CURRENT_DATE + interval '4 year'),
                           PRIMARY KEY(student_id),
                           FOREIGN KEY(student_id)
                               REFERENCES Student(student_id)
                               ON DELETE CASCADE
);

CREATE TABLE Professor(
                          professor_id INTEGER NOT NULL,
                          surname VARCHAR(30) NOT NULL,
                          name VARCHAR(30) NOT NULL,
                          patronymic VARCHAR(30) NULL,
                          degree VARCHAR(15) NULL CHECK (degree ~* '^[кКдД].+[а-яА-Я].+[н].+$'),
                          academic_title VARCHAR(40) NULL,
                          сurrent_position VARCHAR(40) NOT NULL,
                          experience INTEGER NOT NULL,
                          salary MONEY,
                          PRIMARY KEY(professor_id)
);

CREATE TABLE Field(
                      field_id UUID NOT NULL,
                      field_name VARCHAR(100) NOT NULL,
                      structural_unit_id INTEGER NOT NULL REFERENCES Structural_unit(structural_unit_id),
                      professor_id INTEGER NOT NULL REFERENCES Professor(professor_id),
                      ZET INTEGER NOT NULL,
                      PRIMARY KEY(field_id)
);


CREATE TABLE Employment(
                           structural_unit_number INTEGER NOT NULL REFERENCES Structural_unit,
                           professor_id INTEGER NOT NULL REFERENCES Professor,
                           contract_number INTEGER NOT NULL,
                           wage_rate NUMERIC(3,2) NOT NULL,
                           PRIMARY KEY(
                                       structural_unit_number,
                                       professor_id
                               )
);

CREATE TABLE Field_comprehension(
                                    student_id INTEGER NOT NULL REFERENCES Student(student_id),
                                    field UUID NOT NULL REFERENCES field(field_id),
                                    mark INTEGER NOT NULL CHECK (mark >=2 AND mark <=5),
                                    PRIMARY KEY(student_id, field)
);

CREATE TABLE Users(
                      user_id SERIAL NOT NULL PRIMARY KEY,
                      login INTEGER NOT NULL,
                      password VARCHAR NOT NULL,
                      acess_level INTEGER NOT NULL
);

CREATE TABLE debtor_students(
                                ID SERIAL PRIMARY KEY,
                                surname VARCHAR NOT NULL,
                                name VARCHAR NOT NULL,
                                patronymic VARCHAR NOT NULL,
                                group_id VARCHAR NOT NULL,
                                debt_subject_id VARCHAR NOT NULL
);
