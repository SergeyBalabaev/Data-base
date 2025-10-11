#ifndef METHODIST_H
#define METHODIST_H

#include <QWidget>
#include "base/user.h"
#include "subjectsmoderation.h"
#include "journal.h"
#include "teachersmoderation.h"
#include "debtorsmoderation.h"
#include "debtorsjournal.h"

namespace Ui {
class Methodist;
}

/*
 *  Интерфейс методиста
 */

class Methodist : public QWidget
{
    Q_OBJECT

public:
    explicit Methodist(QWidget *parent = nullptr);
    ~Methodist();

    void setCurrentUser(const User user);
    void openTeachersModeration();
    void openSubjectsModeration();
    void openDebtorsModeration();

    void openDebtorsJournal(Subject subject);

public slots:
    void closeJournal();
    void setJournalSubject(Subject subject);
    void openJoural(QString group);

private:
    Ui::Methodist *ui;
    // SubjectSelection *subjects_window;
    // GroupSelection *groups_window;
    SubjectsModeration *subjects_window_;
    TeachersModeration *teachers_window_;
    Journal *journal_window_;
    DebtorsModeration *debtors_window_;
    DebtorsJournal *debtors_journal_window_;

    void configureBoxesMenus();

    User current_methodist_;
};

#endif // METHODIST_H
