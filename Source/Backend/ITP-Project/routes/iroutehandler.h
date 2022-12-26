#ifndef IROUTEHANDLER_H
#define IROUTEHANDLER_H

#include <QTcpSocket>
#include <QString>


class IRouteHandler
{
public:
    virtual void handleRoute(QTcpSocket *socket, const QMap<QString, QString> &parameters) = 0;
};

#endif // IROUTEHANDLER_H
