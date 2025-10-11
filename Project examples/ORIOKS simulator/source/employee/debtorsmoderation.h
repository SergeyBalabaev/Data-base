#ifndef DEBTORSMODERATION_H
#define DEBTORSMODERATION_H

#include <QWidget>
#include <QSqlQuery>

#include "base/subject.h"

// TODO: здесь было бы неплохо наследоваться от одного
// базового класса, как для модерирования предметов,
// так для модерирования должников, возможно, запилю
// в будущем

namespace Ui {
class DebtorsModeration;
}

class DebtorsModeration : public QWidget
{
    Q_OBJECT

public:
    explicit DebtorsModeration(QWidget *parent = nullptr);
    ~DebtorsModeration();

    void searchDebtors();
    void fillDebtorsTable(QSqlQuery query);

    void fillTeachers();
    void fillStructuralUnits();
    void fillGroups();

    std::vector<Subject> subjects_;
    std::map<QString, int> structs_id_;

private:
    Ui::DebtorsModeration *ui;
    void configureDebtorsTable();

signals:
    void debtorsJournalRequested(Subject);

private slots:
    void handleDebtorsJournalRequest(int record_line);

};

#endif // DEBTORSMODERATION_H
