#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QStringLiteral>

#include <QWebSocket>
#include <QWebSocketServer>



class WebSocketServer : public QObject
{
public:
    WebSocketServer(quint16 port, QObject *parent = 0);

private:
    QWebSocketServer m_socketServer;
};

#endif // WEBSOCKETSERVER_H
