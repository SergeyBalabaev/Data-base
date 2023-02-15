--DROP DATABASE Students;
--CREATE DATABASE Students;
DROP TABLE IF EXISTS "Студент" CASCADE;
DROP TABLE IF EXISTS "Структурное подразделение" CASCADE;
DROP TABLE IF EXISTS "Группа";
DROP TABLE IF EXISTS "Студенческий билет";
DROP TABLE IF EXISTS "Преподаватель" CASCADE;
DROP TABLE IF EXISTS "Дисциплина" CASCADE;
DROP TABLE IF EXISTS "Трудоустройство";
DROP TABLE IF EXISTS "Результат освоения дисциплины";

CREATE TABLE "Структурное подразделение"(
    "Номер подразделения" BIGINT PRIMARY KEY CHECK("Номер подразделения" > 0),
    "Тип подразделения" VARCHAR(64) NOT NULL CHECK ("Тип подразделения" = ANY ('{Кафедра, Институт}'::VARCHAR[])),
    "Полное название" TEXT NOT NULL,
    "Сокращенное название" VARCHAR(20) NULL,
    "Руководитель" VARCHAR(40) NOT NULL
);

CREATE TABLE "Группа"(
    "Номер группы" VARCHAR(7) PRIMARY KEY CHECK ("Номер группы" ~* '^[А-Яа-я]+-[МВ0-9]+$'),
    "Форма обучения" VARCHAR(12) NOT NULL CHECK ("Форма обучения" = ANY ('{Очная, Заочная, Очно-заочная}'::VARCHAR[])),
    "Номер структурного подразделения" BIGINT NOT NULL REFERENCES "Структурное подразделение"("Номер подразделения") 
);

CREATE TABLE "Студент"(
    "Номер студенческого билета" BIGINT NOT NULL,
    "Фамилия" VARCHAR(30) NOT NULL,
    "Имя" VARCHAR(30) NOT NULL,
    "Отчество" VARCHAR(30) NULL,
    "Номер группы" VARCHAR(7) NOT NULL,
    "Дата рождения" DATE NOT NULL,
	"Почта" VARCHAR(30) UNIQUE,
	PRIMARY KEY("Номер студенческого билета"),
	CONSTRAINT клГруппа
		FOREIGN KEY("Номер группы") 
			REFERENCES "Группа"("Номер группы")
			ON DELETE CASCADE,
	CONSTRAINT проверка_почты 
		CHECK ("Почта" ~* '^[A-Za-z0-9._+%-]+@[A-Za-z0-9.-]+[.][A-Za-z]+$')
);

CREATE TABLE "Студенческий билет"(
    "Номер" BIGINT NOT NULL,
    "Дата выдачи" DATE NOT NULL DEFAULT CURRENT_DATE,
    "Действителен по" DATE NOT NULL DEFAULT (CURRENT_DATE + interval '4 year'),
	PRIMARY KEY("Номер"),
	FOREIGN KEY("Номер") 
		REFERENCES "Студент"("Номер студенческого билета") 
		ON DELETE CASCADE
);

CREATE TABLE "Преподаватель"(
    "Номер преподавателя" BIGINT NOT NULL,
    "Фамилия" VARCHAR(30) NOT NULL,
    "Имя" VARCHAR(30) NOT NULL,
    "Отчество" VARCHAR(30) NULL,
    "Ученая степень" VARCHAR(15) NULL CHECK ("Ученая степень" ~* '^[кКдД].+[а-яА-Я].+[н].+$'),
    "Ученое звание" VARCHAR(40) NULL,
    "Должность" VARCHAR(20) NOT NULL,
    "Стаж" BIGINT NOT NULL,
	"Оклад" MONEY,
	PRIMARY KEY("Номер преподавателя")
);

CREATE TABLE "Дисциплина"(
    "Номер дисциплины" UUID NOT NULL,
    "Название дисциплины" VARCHAR(40) NOT NULL,
    "Структурное подразделение" BIGINT NOT NULL REFERENCES "Структурное подразделение"("Номер подразделения"),
    "Преподаватель" BIGINT NOT NULL REFERENCES "Преподаватель"("Номер преподавателя"),
    "ЗЕТ" BIGINT NOT NULL,
	PRIMARY KEY("Номер дисциплины")
);


CREATE TABLE "Трудоустройство"(
    "Номер структурного подразделения" BIGINT NOT NULL REFERENCES "Структурное подразделение",
    "Номер преподавателя" BIGINT NOT NULL REFERENCES "Преподаватель",
    "Номер трудового договора" BIGINT NOT NULL,
	"Ставка" NUMERIC(3,2) NOT NULL,
	PRIMARY KEY(
        "Номер структурного подразделения", 
		"Номер преподавателя"
    )
);

CREATE TABLE "Результат освоения дисциплины"(
    "Студент" BIGINT NOT NULL REFERENCES "Студент"("Номер студенческого билета"),
    "Дисциплина" UUID NOT NULL REFERENCES "Дисциплина"("Номер дисциплины"),
    "Оценка" BIGINT NOT NULL CHECK (Оценка >=2 AND Оценка <=5),
	PRIMARY KEY("Студент", "Дисциплина")
);


