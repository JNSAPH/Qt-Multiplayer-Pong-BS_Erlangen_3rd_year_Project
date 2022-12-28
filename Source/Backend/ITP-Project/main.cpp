#include <QCoreApplication>
#include <QFile>

#include <iostream> // std::cout
#include <fstream>

#include "ws/webserver.h"
#include "socket/websocketserver.h"

// Routes
#include "routes/jsontestroute.h"
#include "routes/httptestroute.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    // Create Http Server instance
    HttpServer server;

    // Create WebSocket Server instance
    WebSocketServer socket(1214);

    // Routes
    server.addRoute("/json", "GET", new JSONTestRoute());
    server.addRoute("/http", "GET", new HTTPTestRoute());






    // Start the Http server
    if (!server.start(8080)) {
        qCritical() << "Failed to start server:" << server.errorString();
        return 1;
    }

    return app.exec();
}
