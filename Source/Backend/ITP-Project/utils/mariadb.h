#ifndef MARIADB_H
#define MARIADB_H

#include <QtSql>

class MariaDB
{
public:
    MariaDB(const QString& hostname, const QString& username, const QString& password, const QString& database, int port = 3306);
    ~MariaDB();

    bool open();
    void close();

    QSqlQuery exec(const QString& query);
    bool transaction();
    bool commit();
    bool rollback();

    void printDebugTable(const QString& tableName);

    QSqlDatabase getM_DB();

private:
    QString m_hostname;
    QString m_username;
    QString m_password;
    QString m_database;
    int m_port;

    QSqlDatabase m_db;
};

#endif // MARIADB_H
