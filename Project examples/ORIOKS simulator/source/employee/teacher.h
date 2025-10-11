#ifndef TEACHER_H
#define TEACHER_H

#include <QWidget>
#include <QStackedWidget>

#include "subjectselection.h"
#include "groupselection.h"
#include "debtors.h"
#include "journal.h"
#include "base/user.h"
#include "debtorsjournal.h"

namespace Ui {
class Teacher;
}

/*
 *  Интерфейс преподавателя
 */

class Teacher : public QWidget
{
    Q_OBJECT

public:
    explicit Teacher(QWidget *parent = nullptr);
    ~Teacher();

    void initSubjectsList();
    void setCurrentUser(const User user);

    void setSqlUnit(std::shared_ptr<SqlService> unit);

public slots:
    void setWorkflow(Subject subject);
    void openJoural(QString group);
    void openDebtorsJournal(Subject subject);
    void openGroupSelection(QStringList groups);
    void openSubjectSelecion();
    void openDebtorsSelection();
    void closeJournal();

private:
     Ui::Teacher *ui;

    std::shared_ptr<SqlService> sql_unit_;

    SubjectSelection *subjects_window_;
    GroupSelection *groups_window_;
    Journal *journal_window_;
    Debtors *debtors_window_;
    DebtorsJournal *debtors_journal_window_;

    User current_teacher_;

    void configureStudyBox();


};

#endif // TEACHER_H
