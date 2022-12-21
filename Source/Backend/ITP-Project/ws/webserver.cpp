#include "webserver.h"

HttpServer::HttpServer(QObject* parent)
{
}

HttpServer::~HttpServer()
{
}

void HttpServer::addRoute(const QString& path, std::function<void(QTcpSocket*, const QMap<QString, QString>&)> callback)
{
    m_routes[path] = callback;
}



bool HttpServer::start(quint16 port)
{
    return QTcpServer::listen(QHostAddress::Any, port);
}

QString HttpServer::errorString() const
{
    return QTcpServer::errorString();
}


void HttpServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket* socket = new QTcpSocket(this);
    if (socket->setSocketDescriptor(socketDescriptor))
    {
        connect(socket, &QTcpSocket::readyRead, [socket, this]()
        {
            // Parse the request
            QByteArray requestData = socket->readAll();
            QString requestString(requestData);
            QStringList requestLines = requestString.split("\r\n");
            if (requestLines.empty())
                return;

            QStringList requestLineTokens = requestLines[0].split(" ");
            if (requestLineTokens.size() != 3)
                return;

            QString method = requestLineTokens[0];
            QString path = requestLineTokens[1];
            QString httpVersion = requestLineTokens[2];

            QMap<QString, QString> headers;
            for (int i = 1; i < requestLines.size(); ++i)
            {
                QString line = requestLines[i];
                int index = line.indexOf(":");
                if (index != -1)
                {
                    QString key = line.left(index).trimmed();
                    QString value = line.mid(index + 1).trimmed();
                    headers[key] = value;
                }
            }

            // Handle the request
            auto it = m_routes.find(path);
            if (it != m_routes.end())
                it.value()(socket, headers);
            else
            {
                // Return a 404 response
                QString response = "HTTP/1.1 404 Not Found\r\n\r\n";
                socket->write(response.toUtf8());
                socket->close();
            }
        });

        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    }
    else
    {
        delete socket;
    }
}
