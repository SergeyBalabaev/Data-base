#ifndef TEACHERSMODERATION_H
#define TEACHERSMODERATION_H

#include <QWidget>
#include <base/subject.h>

namespace Ui {
class TeachersModeration;
}

class TeachersModeration : public QWidget
{
    Q_OBJECT

public:
    explicit TeachersModeration(QWidget *parent = nullptr);
    ~TeachersModeration();

private:
    Ui::TeachersModeration *ui;
    void fillTeachers();

    Subject current_subject_;
    int current_teacher_id_; // Использовать структуру User тут нецелесообразно

    void updateFieldTable();
    void updateEmploymentTable();

private slots:
    void searchByDiscipline();
    void save();

};

#endif // TEACHERSMODERATION_H
