#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QString>

#include <string>
#include "../utils/ws_utils.h"

class HttpServer : public QTcpServer {
    Q_OBJECT
public:
    HttpServer(QObject* parent = 0);
    ~HttpServer();
    bool start(quint16 port);
    QString errorString() const;
    void addRoute(const QString& path, const QString& method, std::function<void(QTcpSocket*, const QMap<QString, QString>&)> callback);

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    struct Route
        {
            QString method;
            std::function<void(QTcpSocket*, const QMap<QString, QString>&)> callback;
        };
    QMap<QString, Route> m_routes;
};

#endif // WEBSERVER_H
