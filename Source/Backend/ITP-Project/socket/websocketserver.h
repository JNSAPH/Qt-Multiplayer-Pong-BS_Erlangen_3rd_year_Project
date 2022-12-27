#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>

#include <QObject>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)
QT_FORWARD_DECLARE_CLASS(QString)


class WebSocketServer : public QObject
{
    Q_OBJECT

public:
    explicit WebSocketServer(quint16 port, QObject *parent = nullptr);
    ~WebSocketServer();

private slots:
    void onNewConnection();
    void processMessage(const QString &message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;

};

#endif // WEBSOCKETSERVER_H
