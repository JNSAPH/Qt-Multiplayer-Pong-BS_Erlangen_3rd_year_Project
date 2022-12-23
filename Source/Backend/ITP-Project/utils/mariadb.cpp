#include "mariadb.h"

MariaDB::MariaDB(const QString& hostname, const QString& username, const QString& password, const QString& database, int port)
    : m_hostname(hostname)
    , m_username(username)
    , m_password(password)
    , m_database(database)
    , m_port(port)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
}

MariaDB::~MariaDB()
{
    close();
}

bool MariaDB::open()
{
    m_db.setHostName(m_hostname);
    m_db.setUserName(m_username);
    m_db.setPassword(m_password);
    m_db.setDatabaseName(m_database);
    m_db.setPort(m_port);

    return m_db.open();
}

void MariaDB::close()
{
    m_db.close();
}

QSqlQuery MariaDB::exec(const QString& query)
{
    return m_db.exec(query);
}

bool MariaDB::transaction()
{
    return m_db.transaction();
}

bool MariaDB::commit()
{
    return m_db.commit();
}

bool MariaDB::rollback()
{
    return m_db.rollback();
}

QSqlDatabase MariaDB::getM_DB() {
    return m_db;
}
