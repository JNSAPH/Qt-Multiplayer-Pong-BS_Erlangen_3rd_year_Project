#include <QCoreApplication>
#include <QFile>

#include <iostream> // std::cout
#include <fstream>

#include "ws/webserver.h"

// Routes
#include "routes/jsontestroute.h"
#include "routes/httptestroute.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
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
