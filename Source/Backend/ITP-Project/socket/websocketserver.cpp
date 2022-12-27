#include "websocketserver.h"

#include <QtWebSockets>
#include <QtCore>

#include <cstdio>
using namespace std;

QT_USE_NAMESPACE

static QString getIdentifier(QWebSocket *peer)
{
    return QStringLiteral("%1:%2").arg(peer->peerAddress().toString(),
                                       QString::number(peer->peerPort()));
}

WebSocketServer::WebSocketServer(quint16 port, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Chat Server"),
                                            QWebSocketServer::NonSecureMode,
                                            this))
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        QTextStream(stdout) << "Chat Server listening on port " << port << '\n';
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &WebSocketServer::onNewConnection);
    }
}


WebSocketServer::~WebSocketServer()
{
    m_pWebSocketServer->close();
}

void WebSocketServer::processMessage(const QString &message)
{
    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
    for (QWebSocket *pClient : std::as_const(m_clients)) {
        if (pClient != pSender) //don't echo message back to sender
            pClient->sendTextMessage(message);
    }
}

void WebSocketServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    QTextStream(stdout) << getIdentifier(pClient) << " disconnected!\n";
    if (pClient)
    {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
//! [socketDisconnected]
