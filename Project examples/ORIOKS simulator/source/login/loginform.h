#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <map>
#include "base/user.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();
    void setLoginFormStyle(const QString &styleSheet);

    enum AcessLevel {
        student, teacher, methodist
    };

signals:
    void authorized(User);
    void authorisationFailed();

private slots:
    void authoriseRequested();
    void startAnotherAttempt();

private:
    Ui::LoginForm *ui;

//    std::map<QString, AcessLevel> acess_levels {
//        {"STUDENT", AcessLevel::student},
//        {"TEACHER", AcessLevel::teacher},
//        {"METHODIST", AcessLevel::methodist}
//    };

    void showLoginError();

    User current_user_;
};

#endif // LOGINFORM_H
