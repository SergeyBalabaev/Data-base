#include <QSqlQuery>

#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground, true);

    ui->log_err_msg->setVisible(false);

    // connects
    connect(ui->authorise_button, &QPushButton::clicked, this, &LoginForm::authoriseRequested);

    //////////////////////////
    /// Debug purposes only //
    //////////////////////////

    // Teacher:
     ui->login_edit->setText("81007");
     ui->password_edit->setText("123456");

    // Student:
    //ui->login_edit->setText("856271");
    //ui->password_edit->setText("2001-06-03");

    // Methodist:
   //  ui->login_edit->setText("90010");
   //  ui->password_edit->setText("123456");
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::setLoginFormStyle(const QString &styleSheet)
{
    setStyleSheet(styleSheet); // Устанавливаем стиль для формы входа
}

void LoginForm::authoriseRequested()
{
    // Получаю значения с полей:
    QString requested_login = ui->login_edit->text();
    QString requested_password = ui->password_edit->text();

    // Сверяю пароль:
    QSqlQuery login_query;
    login_query.prepare("SELECT password, acess_level FROM users "
                        "WHERE login = :login");
    login_query.bindValue(":login", requested_login);

    // Делаю запрос и получаю первый результат:
    login_query.exec();

    if (login_query.next()) {

        QString valid_password = login_query.value(0).toString();

        if (requested_password == valid_password) {
            // Создаю сеанс для пользователя
            current_user_.setUserId((ui->login_edit->text()).toInt());
            current_user_.setAcessLevel(static_cast<User::AcessLevel>(login_query.value(1).toInt()));

            // Получаю уровень доступа учетной записи
            // current_user_.acess_level = static_cast<User::AcessLevel>(login_query.value(1).toInt());

            // Вход успешен
            emit authorized(current_user_);
        } else {
            // Авторизация неудачна
            showLoginError();
        }
    } else {
        showLoginError();
    }
}

void LoginForm::showLoginError()
{
    ui->login_edit->clear();
    // ui->password_edit->clear();
    ui->log_err_msg->setVisible(true);
}

void LoginForm::startAnotherAttempt()
{
    ui->log_err_msg->setVisible(false);
}

