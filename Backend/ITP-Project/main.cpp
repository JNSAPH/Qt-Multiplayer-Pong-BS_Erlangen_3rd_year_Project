#include <QCoreApplication>

#include <iostream>
#include <QFile>

#include <fstream>

#include "ws/webserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    HttpServer server;

    // Add routes to the server
    server.addRoute("/main", [](QTcpSocket* socket, const QMap<QString, QString>& headers)
    {
        std::string content;

        std::ifstream f("C:/Users/JNSAP/Documents/GitHub/ITP-Project-1/Backend/ITP-Project/index.html");

        if(f.good()) {
            std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
            content = str;
        } else {
            std::cout << "File not found!" << std::endl;
        }

        std::ostringstream oss;

        oss << "HTTP/1.1 200 OK\r\n";
        oss << "Cache-Control: no-cache, private\r\n";
        oss << "Content-Type: text/html\r\n";
        oss << "Content-Length: " << content.length() << "\r\n";
        oss << "\r\n";
        oss << content;

        socket->write(oss.str().c_str());
        f.close();
    });

    // Start the server
    if (!server.start(8080))
    {
        qCritical() << "Failed to start server:" << server.errorString();
        return 1;
    }

    return app.exec();
}

