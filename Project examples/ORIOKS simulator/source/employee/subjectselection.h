#ifndef SUBJECTSELECTION_H
#define SUBJECTSELECTION_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <memory>

#include "sql_service/sqlservice.h"
#include "base/subject.h"
#include "base/user.h"

using std::vector;

namespace Ui {
class SubjectSelection;
}

class SubjectSelection : public QWidget
{
    Q_OBJECT

public:

    explicit SubjectSelection(QWidget *parent = nullptr);
    ~SubjectSelection();

    void fillSubjectsTable();
    void handleGroupListRequest(int row);

    QString getSubjectId(QString subject_name);

    void setCurrentUser(User user);
    void setSqlService(std::shared_ptr<SqlService> database_unit_);

private:
    Ui::SubjectSelection *ui;
    std::shared_ptr<SqlService> database_unit_;

    std::map<QString, QString> subjects_id_;
    User current_user_;


signals:
    void subjectSelected(Subject);
    void groupListRequested(QStringList);
};

#endif // SUBJECTSELECTION_H
