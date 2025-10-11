#ifndef DIARY_H
#define DIARY_H

#include <QWidget>
#include <QLabel>
#include "base/user.h"

#include <QSqlQuery>

namespace Ui {
class Diary;
}

class Diary : public QWidget
{
    Q_OBJECT

public:
    explicit Diary(QWidget *parent = nullptr);
    ~Diary();

    void setStudent(User user);
    void loadMarks();
    void fillDiaryMarks(QSqlQuery marks_query);

private slots:
    void searchBySubject(); // !
    void textEdited();

private:
    Ui::Diary *ui;
    User current_student_;
    //int student_id_;

};

#endif // DIARY_H
