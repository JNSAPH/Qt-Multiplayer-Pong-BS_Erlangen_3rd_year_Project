#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QWidget>



class HttpRequest
{
public:
    static HttpRequest* instance();
    void post(const QString &url,const QByteArray &data,QMap<QByteArray,QByteArray> headers = QMap<QByteArray,QByteArray>());
    void get(const QString &url,QMap<QByteArray,QByteArray> headers = QMap<QByteArray,QByteArray>());
    QNetworkReply* getReply() const;
private:
    HttpRequest();
    static HttpRequest* m_instance;
    QNetworkAccessManager* m_manager;
    QNetworkReply* m_reply;
    void onResult(QNetworkReply *reply);
};

#endif // HTTPREQUEST_H
