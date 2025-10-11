#ifndef JOURNAL_H
#define JOURNAL_H

#include <map>

#include <QWidget>
#include <QSqlQuery>

#include "base/subject.h"



namespace Ui {
class Journal;
}

class Journal : public QWidget
{
    Q_OBJECT

public:
    explicit Journal(QWidget *parent = nullptr);

    void openGroup(QString group);
    void setCurrentSubject(Subject subject);

    ~Journal();

private:
    Ui::Journal *ui;

    void fillMarks(QSqlQuery marks_record);
    void configurateView();

    QString group_name_;
    Subject current_subject_;

    std::map<int, int> students_id_;

public slots:
    void updateDatabaseGrades();

signals:
    void goBack();
};

#endif // JOURNAL_H
