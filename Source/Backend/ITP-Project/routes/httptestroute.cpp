#include "httptestroute.h"

HTTPTestRoute::HTTPTestRoute()
{

}

void HTTPTestRoute::handleRoute(QTcpSocket *socket, const QMap<QString, QString> &parameters)
{
    std::string response = WSUtils::createHTMLResponse("<h1>Sex ... mit männern </h1>");

    socket->write(response.c_str());
    socket->close();
}
