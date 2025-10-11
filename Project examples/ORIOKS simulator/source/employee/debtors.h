#ifndef DEBTORS_H
#define DEBTORS_H

#include <QWidget>
#include <QSqlQuery>
#include "base/subject.h"
#include "base/user.h"


namespace Ui {
class debtors;
}

class Debtors : public QWidget
{
    Q_OBJECT

public:
    void setDebtorTableParameters();
    void setCurrentUser(User user);

    void fillDebtorsGroupsTable(QSqlQuery debtors_query);
    void findContingent();
    explicit Debtors(QWidget *parent = nullptr);
    ~Debtors();

private:
    Ui::debtors *ui;
    User current_user_;
    std::vector<Subject> current_subjects_;

private slots:
    void handleDebtorsJournalRequest(int record_line);

signals:
    void debtorsJournalRequested(Subject subject);

};

#endif // DEBTORS_H
