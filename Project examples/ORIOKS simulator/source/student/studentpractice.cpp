#include "studentpractice.h"
#include "ui_studentpractice.h"

StudentPractice::StudentPractice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentPractice)
{
    ui->setupUi(this);

    // TODO
}

StudentPractice::~StudentPractice()
{
    delete ui;
}
