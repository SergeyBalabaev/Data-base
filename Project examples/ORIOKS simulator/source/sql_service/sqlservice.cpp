#include "sqlservice.h"
#include "configuratedatabase.h"

SqlService::SqlService()
{
    this->database_name_ = DATABASE_NAME;
    this->user_name_ = USER_NAME;
    this->password_ = PASSWORD;
    this->host_name_ = HOST_NAME;
}

void SqlService::databaseConnect()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(host_name_); // IP-адрес вашей виртуальной машины Ubuntu (см. на виртуалке)
    db.setPort(5432); // порт по умолчанию для PostgreSQL
    db.setDatabaseName(database_name_); // имя вашей базы данных (см. на виртуалке)
    db.setUserName(user_name_); // ваше имя пользователя для базы данных (см. на виртуалке)
    db.setPassword(password_); // ваш пароль для базы данных (см. на виртуалке)
    db.setConnectOptions("client_encoding=UTF8");

    if (!db.open()) {
        qDebug() << "Failed to connect to database.";
        qDebug() << "Error: ";
        qDebug() << db.lastError().text();
    } else {
        qDebug() << "Connected to database succesfully!";
    }
}

QSqlQuery SqlService::runQuery(QString content)
{
    // Выполнение sql запроса
    // TODO: оставить как свободную функцию, чтобы можно было "поиграться"

    QSqlQuery query;
    query.exec(content);

    // Обработка

    if (query.lastError().isValid()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
    } else {
        // Запрос выполнен успешно
    }
    return query;
}

