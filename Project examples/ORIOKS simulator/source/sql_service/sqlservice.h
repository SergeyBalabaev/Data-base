#ifndef SQLSERVICE_H
#define SQLSERVICE_H

#include <memory.h>
#include <QObject>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>


class SqlService
{
public:
    SqlService();
    void databaseConnect();

    QSqlQuery runQuery(QString content);

private:
    QSqlDatabase db;

    QString database_name_;
    QString user_name_;
    QString password_;
    QString host_name_;

    bool getConnectionStatus();
};

#endif // SQLSERVICE_H
