#include <QCoreApplication>
#include <QFile>

#include <iostream> // std::cout
#include <fstream>

#include "ws/webserver.h"
#include "utils/ws_utils.h"
#include "utils/jsonutils.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    HttpServer server;

    server.addRoute("/json", "GET", [](QTcpSocket *socket, const QMap<QString, QString> &headers) {

        std::map<std::string, JSONUtils::Value> data{
          {"key1", 42},
          {"key2", true},
          {"key3", "hello"}
        };
        std::string json = JSONUtils::generateJSON(data);


        std::string response = WSUtils::createJSONResponse(json);

        socket->write(response.c_str());
        socket->close(); });

    // Start the server
    if (!server.start(8080)) {
        qCritical() << "Failed to start server:" << server.errorString();
        return 1;
    }

    return app.exec();
}
