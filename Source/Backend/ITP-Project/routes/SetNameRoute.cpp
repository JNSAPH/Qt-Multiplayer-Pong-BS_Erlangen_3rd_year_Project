#include "SetNameRoute.h"

//setName

SetNameRoute::SetNameRoute() { }

void SetNameRoute::handleRoute(QTcpSocket *socket, const QMap<QString, QString> &parameters)
{
    Score::updateName(parameters["UUID"], parameters["Name"]);

    std::string response = WSUtils::createJSONResponse("jsonDocument.toJson().toStdString()");
    socket->write(response.c_str());
    socket->close();
}
