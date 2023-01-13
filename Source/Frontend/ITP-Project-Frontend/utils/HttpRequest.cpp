#include "HttpRequest.h"

HttpRequest* HttpRequest::m_instance = 0;

HttpRequest::HttpRequest()
{

}

HttpRequest* HttpRequest::instance() {
    if (!m_instance) {
        m_instance = new HttpRequest;
    }
    return m_instance;
}

void HttpRequest::post(const QString &url,const QByteArray &data,QMap<QByteArray,QByteArray> headers){
    QNetworkRequest request((QUrl(url)));
    // Adding headers
    for(auto key : headers.keys()){
        request.setRawHeader(key,headers.value(key));
    }
    // Send post request
    m_manager->post(request,data);
}


void HttpRequest::get(const QString &url,QMap<QByteArray,QByteArray> headers ){
    QNetworkRequest request((QUrl(url)));
    // Adding headers
    for(auto key : headers.keys()){
        request.setRawHeader(key,headers.value(key));
    }
    // Send get request
    m_manager->get(request);
}

QNetworkReply* HttpRequest::getReply() const {
    return m_reply;
}
