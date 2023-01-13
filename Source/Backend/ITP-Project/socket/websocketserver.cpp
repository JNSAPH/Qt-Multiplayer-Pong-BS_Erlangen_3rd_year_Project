#include "websocketserver.h"

// Define the static m_sockets variable outside of the class definition
QList<QWebSocket *> WebSocketServer::m_sockets;

// Assign an initial value to the m_sockets variable



WebSocketServer::WebSocketServer(quint16 port, QObject *parent) :
    QObject(parent),
    m_socketServer(QStringLiteral("ITP-Project Server"), QWebSocketServer::NonSecureMode, this)
{
    if (!m_socketServer.listen(QHostAddress::LocalHost, port)) {
        qFatal("Failed to open web socket server.");
    }
    qDebug() << "WebSocket server listening on port" << m_socketServer.serverPort();
    connect(&m_socketServer, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
}

void WebSocketServer::onNewConnection() {
    QWebSocket *socket = m_socketServer.nextPendingConnection();


    // Connect to the socket's signals
    connect(socket, &QWebSocket::textMessageReceived, this, &WebSocketServer::onTextMessageReceived);
    connect(socket, &QWebSocket::binaryMessageReceived, this, &WebSocketServer::onBinaryMessageReceived);
    connect(socket, &QWebSocket::disconnected, this, &WebSocketServer::onSocketDisconnected);

    m_sockets.append(socket);

    // Send a greeting message to the client
    std::map<std::string, JSONUtils::Value> data{
      {"code", 200},
      {"message", "Connection established to SocketServer!"}
    };

    socket->sendTextMessage(QString::fromStdString(JSONUtils::generateJSON(data)));
}

void WebSocketServer::onTextMessageReceived(QString message) {
    qDebug() << "Received message:" << message;

    // Send a response back to the client
    QWebSocket *senderSocket = qobject_cast<QWebSocket *>(sender());
    if (senderSocket) {
        std::map<std::string, JSONUtils::Value> data{
          {"code", 201},
          {"message", "Received Message!"},
          {"received_message", message.toStdString()}
        };
        senderSocket->sendTextMessage(QString::fromStdString(JSONUtils::generateJSON(data)));
    }
}

void WebSocketServer::onBinaryMessageReceived(QByteArray message) {
    qDebug() << "Received binary message of size" << message.size() << "bytes";

    // Send a response back to the client
    QWebSocket *senderSocket = qobject_cast<QWebSocket *>(sender());
    if (senderSocket) {
        std::map<std::string, JSONUtils::Value> data{
          {"code", 202},
          {"message", "Received Binary Message!"},
          {"received_message", message.toStdString()}
        };
        senderSocket->sendBinaryMessage(QString::fromStdString(JSONUtils::generateJSON(data)).toUtf8());
    }
}

void WebSocketServer::onSocketDisconnected() {
    // Get the disconnected socket
    QWebSocket *socket = qobject_cast<QWebSocket *>(sender());

    qDebug() << "Disconnected one User.";

    // Remove the socket from the list of connected sockets
    m_sockets.removeOne(socket);

    // Delete the socket
    socket->deleteLater();
}

void WebSocketServer::broadcast(const QString &message) {
    // Iterate over the list of connected sockets
    for (auto socket : m_sockets) {
        // Send the message to the socket
        socket->sendTextMessage(message);
    }
}
