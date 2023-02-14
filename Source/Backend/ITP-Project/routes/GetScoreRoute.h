#ifndef GETSCOREROUTE_H
#define GETSCOREROUTE_H

#include "iroutehandler.h"
#include "../utils/jsonutils.h"
#include "../utils/ws_utils.h"

#include "../utils/score.h"

#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

class GetScoreRoute : public IRouteHandler
{
public:
    GetScoreRoute();
    void handleRoute(QTcpSocket *socket, const QMap<QString, QString> &parameters) override;
};

#endif // GETSCOREROUTE_H
