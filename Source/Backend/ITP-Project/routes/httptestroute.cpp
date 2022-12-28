#include "httptestroute.h"

HTTPTestRoute::HTTPTestRoute()
{

}

#include "../socket/websocketserver.h"

void HTTPTestRoute::handleRoute(QTcpSocket *socket, const QMap<QString, QString> &parameters)
{
    std::string response = WSUtils::createHTMLResponse("<h1>Sex ... mit männern </h1>");

    WebSocketServer::broadcast("Fortnite");


    socket->write(response.c_str());
    socket->close();
}
