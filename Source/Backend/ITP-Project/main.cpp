#include <QCoreApplication>
#include <QFile>

#include <iostream> // std::cout
#include <fstream>

#include "socket/websocketserver.h"
#include "Pong/game.h"

#include <QTimer>
#include <QThread>

// Routes
#include "routes/GetScoreRoute.h"
#include "ws/webserver.h"

// DB Login
// Username: itpundefined

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    // Configure qDebug
    qputenv("QT_MESSAGE_PATTERN", "%{file}:%{line} %{message}");

    // Create WebSocket Server instance
    WebSocketServer& wss = WebSocketServer::getInstance(1215);

    Game& game = Game::getInstance();

    // Create WebServer instance
    HttpServer server;

    // Add Route
    server.addRoute("/getScore", "GET", new GetScoreRoute());

    // Start server on port 8080
    if (!server.start(1216)) {
        // If server failed to start, print error and exit
        qCritical() << "Failed to start server:" << server.errorString();
        return 1;
    }

    return app.exec();
}
