#include <QVBoxLayout>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStackedWidget>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initDatabaseInterfaces();

    // Stacked widget является скелетом приложения
    stackedWidget = new QStackedWidget();

    stackedWidget->addWidget(login_form_);
    stackedWidget->addWidget(teacher_interface_);
    stackedWidget->addWidget(student_interface_);
    stackedWidget->addWidget(methodist_interface);

    stackedWidget->setCurrentWidget(login_form_);

    setCentralWidget(stackedWidget);

    // connects
    connect(login_form_, &LoginForm::authorized, this, &MainWindow::logIn);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initDatabaseInterfaces()
{
    database_unit_ = std::make_unique<SqlService>();
    database_unit_->databaseConnect();

    // Setting for interfaces
    teacher_interface_ = new Teacher();
    teacher_interface_->setSqlUnit(database_unit_);

    login_form_ = new LoginForm();
    student_interface_ = new Student();
    methodist_interface = new Methodist();
}

void MainWindow::logIn(User user)
{
    if (user.getAcessLevel() == User::teacher) {
        stackedWidget->setCurrentWidget(teacher_interface_);
        teacher_interface_->setCurrentUser(user);
        teacher_interface_->initSubjectsList();
    } else if (user.getAcessLevel() == User::methodist) {
        stackedWidget->setCurrentWidget(methodist_interface);
        methodist_interface->setCurrentUser(user);
    } else {
        student_interface_->setCurrentUser(user);
        stackedWidget->setCurrentWidget(student_interface_);
    }
}


