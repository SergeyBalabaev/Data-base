#include "student.h"
#include "ui_student.h"

Student::Student(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Student)
{
    ui->setupUi(this);

    diary_ = new Diary();
    // Добавляю в список виджетов:
    ui->stackedWidget->addWidget(diary_);
    ui->stackedWidget->setCurrentWidget(diary_);

    // Связываю сигналы и слоты:
    connect(ui->diary_button, &QPushButton::clicked, this, &Student::openDiary);
    connect(ui->homepage_button, &QPushButton::clicked, this, &Student::openHomePage);
    connect(ui->practice_button, &QPushButton::clicked, this, &Student::openPracticePage);
    connect(ui->requests_button, &QPushButton::clicked, this, &Student::openRequestsPage);
}

Student::~Student()
{
    delete ui;
}

void Student::setCurrentUser(User user)
{
    current_student_ = user;
    diary_->setStudent(current_student_);
    ui->homepage_button->setText(current_student_.getFullUsername());
}

void Student::openDiary()
{
    diary_->loadMarks();
    ui->stackedWidget->setCurrentWidget(diary_);
}

void Student::openHomePage()
{
    // TODO
}

void Student::openPracticePage()
{
    // TODO
}

void Student::openRequestsPage()
{
    // TODO
}
