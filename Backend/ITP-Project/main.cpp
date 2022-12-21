#include <QCoreApplication>
#include <QFile>

#include <iostream>     // std::cout
#include <sstream>      // std::ostringstream
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

        std::cout << "Main Route" << std::endl;

        std::ifstream f("/Users/jonas/Documents/GitHub/ITP-Project-1/Backend/ITP-Project/index.html ");

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
        oss << content;

        socket->write(oss.str().c_str());
        f.close();
        socket->close();
    });

    server.addRoute("/json", [](QTcpSocket* socket, const QMap<QString, QString>& headers)
    {
        // write a valid http json response and send, then close the socket
        std::ostringstream oss;
        oss << "HTTP/1.1 200 OK\r\n";
        oss << "Content-Type: application/json\r\n";
        oss << "Content-Length: 12\r\n";
        oss << "\r\n";
        oss << "{\"ab\": \"12\"}";

        std::cout << oss.str() << std::endl;

        socket->write(oss.str().c_str());
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

