#ifndef DEBTORSJOURNAL_H
#define DEBTORSJOURNAL_H

#include <QWidget>
#include <QSqlQuery>

#include "base/subject.h"


namespace Ui {
class DebtorsJournal;
}

class DebtorsJournal : public QWidget
{
    Q_OBJECT

public:
    explicit DebtorsJournal(QWidget *parent = nullptr);
    ~DebtorsJournal();

    void openSelectedSubject(Subject subject);
    void fillDebtorsList(QSqlQuery query);
    // void setCurrentSubject (Subject subject);
    void setJournalTableParameters();

private:
    Ui::DebtorsJournal *ui;
    // User current_user_;
    // Subject current_subject_;



signals:
    void goBack();
};

#endif // DEBTORSJOURNAL_H
