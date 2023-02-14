#ifndef SETNAMEROUTE_H
#define SETNAMEROUTE_H

#include "iroutehandler.h"
#include "../utils/jsonutils.h"
#include "../utils/ws_utils.h"

#include "../utils/score.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

class SetNameRoute : public IRouteHandler
{
public:
    SetNameRoute();
    void handleRoute(QTcpSocket *socket, const QMap<QString, QString> &parameters) override;
};

#endif // SETNAMEROUTE_H
