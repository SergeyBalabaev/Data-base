#ifndef STUDENT_H
#define STUDENT_H

#include <QWidget>
#include "diary.h"
#include "base/user.h"

namespace Ui {
class Student;
}

/*
 *  Интерфейс студента
 */

class Student : public QWidget
{
    Q_OBJECT

public:
    explicit Student(QWidget *parent = nullptr);
    ~Student();

    void setCurrentUser(User user);

private:
    Ui::Student *ui;
    int user_id_;

    User current_student_;
    Diary *diary_;

private slots:
    void openDiary();
    void openHomePage();
    void openPracticePage();
    void openRequestsPage();

};

#endif // STUDENT_H
