#include "websocketserver.h"

WebSocketServer::WebSocketServer(quint16 port, QObject *parent) :
    QObject(parent),
    m_socketServer(QStringLiteral("ITP-Project Server"), QWebSocketServer::NonSecureMode, this)
{
    if (!m_socketServer.listen(QHostAddress::LocalHost, port)) {
        qFatal("Failed to open web socket server.");
    }
    qDebug() << "WebSocket server listening on port" << m_socketServer.serverPort();
}
