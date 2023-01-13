#ifndef REQUESTQUEUEROUTE_H
#define REQUESTQUEUEROUTE_H

#include "iroutehandler.h"
#include "../utils/jsonutils.h"
#include "../utils/ws_utils.h"
#include "../gameManager/queuemanager.h"

class RequestQueueRoute : public IRouteHandler
{
public:
    RequestQueueRoute();
    void handleRoute(QTcpSocket *socket, const QMap<QString, QString> &parameters) override;
};

#endif // REQUESTQUEUEROUTE_H
