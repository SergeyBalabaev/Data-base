#ifndef SUBJECTSMODERATION_H
#define SUBJECTSMODERATION_H

#include <QWidget>
#include <QSqlQuery>
#include "base/user.h"
#include <base/subject.h>


namespace Ui {
class SubjectsModeration;
}

class SubjectsModeration : public QWidget
{
    Q_OBJECT

public:
    explicit SubjectsModeration(QWidget *parent = nullptr);
    ~SubjectsModeration();

    void fillUIOptions();
    void setCurrentUser(User user);

    void configureTableParameters();

private slots:
    void searchSubjects();
    void handleJournalRequest(int record_line);

private:
    Ui::SubjectsModeration *ui;
    User current_user_;

    // std::map<QString, QString> subjects_id_;
    std::vector<Subject> subjects_;
    std::map<QString, int> structs_id_;

    void fillTeachers();
    void fillStructuralUnits();
    void fillGroups();

    void fillTableAfterSearch(QSqlQuery subjects_query);

signals:
    void journalRequested(QString);
    void subjectSelected(Subject);

};

#endif // SUBJECTSMODERATION_H
