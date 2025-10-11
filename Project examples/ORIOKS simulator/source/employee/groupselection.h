#ifndef GROUPSELECTION_H
#define GROUPSELECTION_H

#include <QWidget>
#include <QPushButton>
#include "base/subject.h"

namespace Ui {
class GroupSelection;
}

class GroupSelection : public QWidget
{
    Q_OBJECT

public:
    explicit GroupSelection(QWidget *parent = nullptr);
    ~GroupSelection();

    void fillGroups(QStringList groups);
    void setCurrentSubject(Subject subject);

private slots:
    void handleJournalRequest(int record_line);

private:
    Ui::GroupSelection *ui;
    Subject current_subject_;

signals:
    void journalRequested(QString);
    void goBack();
};

#endif // GROUPSELECTION_H
