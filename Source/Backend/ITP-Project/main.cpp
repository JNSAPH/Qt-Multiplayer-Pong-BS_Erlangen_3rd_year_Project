#include <QCoreApplication>
#include <QFile>

#include <iostream>     // std::cout
#include <fstream>

#include "ws/webserver.h"
#include "utils/ws_utils.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    HttpServer server;

    server.addRoute("/json", [](QTcpSocket* socket, const QMap<QString, QString>& headers)
    {
        // Itterate through the headers
        for (auto it = headers.begin(); it != headers.end(); ++it) {
            //std::cout << it.key().toStdString() << ": " << it.value().toStdString() << std::endl;
        }

        std::string response = WSUtils::createJSONResponse("{\"Code\": \"200\", \"Message\": \"JSON Responses work!\"}");

        socket->write(response.c_str());
        socket->close();
    });


    // Start the server
    if (!server.start(8080))
    {
        qCritical() << "Failed to start server:" << server.errorString();
        return 1;
    }

    return app.exec();
}

