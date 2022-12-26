#include <QCoreApplication>
#include <QFile>

#include <iostream> // std::cout
#include <fstream>

#include "ws/webserver.h"
#include "utils/mariadb.h"

// Routes
#include "routes/jsontestroute.h"
#include "routes/httptestroute.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Database Connection
    MariaDB db("85.214.124.142", "itpundefined", "RNDoi76fYcYpesKEjPyk", "testITP");
    if (!db.open()) {
        qCritical() << "Error opening database:" << db.getM_DB().lastError().text();
        return 1;
    } else {
        std::cout << "Connected to DB" << std::endl;
    }

    // Test
    QSqlQuery query = db.exec("SELECT * FROM test_table;");
    qDebug() << db.getM_DB().lastError().text();
    while (query.next()) {
        QString tableName = query.value(0).toString();
        qDebug() << tableName;
    }

    db.printDebugTable("test_table");

    db.close();




    // Create Server instance
    HttpServer server;

    // Routes
    server.addRoute("/json", "GET", new JSONTestRoute());
    server.addRoute("/http", "GET", new HTTPTestRoute());


    // Start the server
    if (!server.start(8080)) {
        qCritical() << "Failed to start server:" << server.errorString();
        return 1;
    }

    return app.exec();
}
