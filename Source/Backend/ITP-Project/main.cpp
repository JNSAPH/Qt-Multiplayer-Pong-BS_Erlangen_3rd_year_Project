#include <QCoreApplication>
#include <QFile>

#include <iostream> // std::cout
#include <fstream>

#include "ws/webserver.h"
#include "utils/ws_utils.h"
#include "utils/jsonutils.h"
#include "utils/mariadb.h"

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
    QSqlQuery query = db.exec("SELECT DATABASE();");
    qDebug() << db.getM_DB().lastError().text();
    while (query.next()) {
        QString tableName = query.value(0).toString();
        qDebug() << "Table:" << tableName;
    }

    db.close();




    // Create Server instance
    HttpServer server;

    // JSON Test Route
    server.addRoute("/json", "GET", [](QTcpSocket *socket, const QMap<QString, QString> &headers) {

        std::map<std::string, JSONUtils::Value> data{
          {"code", 200},
          {"message", "JSON Generator works!"},
          {"bool test", true}
        };
        std::string json = JSONUtils::generateJSON(data);
        std::string response = WSUtils::createJSONResponse(json);

        socket->write(response.c_str());
        socket->close();
    });

    server.addRoute("/html", "GET", [](QTcpSocket *socket, const QMap<QString, QString> &headers) {
        std::string response = WSUtils::createHTMLResponse("<h1>Sex ... mit männern </h1>");

        socket->write(response.c_str());
        socket->close();
    });


    // Start the server
    if (!server.start(8080)) {
        qCritical() << "Failed to start server:" << server.errorString();
        return 1;
    }

    return app.exec();
}
