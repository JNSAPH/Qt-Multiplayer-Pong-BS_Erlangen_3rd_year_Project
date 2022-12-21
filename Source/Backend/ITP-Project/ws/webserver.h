#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QString>

#include <string>

class HttpServer : public QTcpServer {
    Q_OBJECT
public:
    HttpServer(QObject* parent = 0);
    ~HttpServer();
    bool start(quint16 port);
    QString errorString() const;
    void addRoute(const QString& path, std::function<void(QTcpSocket*, const QMap<QString, QString>&)> callback);

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    QMap<QString, std::function<void(QTcpSocket*, const QMap<QString, QString>&)>> m_routes;
};

#endif // WEBSERVER_H
