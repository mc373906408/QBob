#include "HttpMsg.h"

HttpMsg& HttpMsg::getInstance()
{
    static HttpMsg instance;
    return instance;
}

HttpMsg::HttpMsg()
{

}
HttpMsg::~HttpMsg()
{

}


QString HttpMsg::RequestPostForm(bool enablehttps,const QString &url, const QByteArray &data)
{

    QNetworkAccessManager qnam;
    const QUrl aurl( url );
    QNetworkRequest qnr( aurl );

    if(enablehttps)
    {
        QSslConfiguration config = qnr.sslConfiguration();
        config.setPeerVerifyMode(QSslSocket::VerifyNone);
        config.setProtocol(QSsl::TlsV1_3);
        qnr.setSslConfiguration(config);
    }

    qnr.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    qnr.setHeader(QNetworkRequest::ContentLengthHeader,data.size());

    QNetworkReply *reply = qnam.post( qnr, data );

    QEventLoop eventloop;
    connect( reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
    eventloop.exec( QEventLoop::ExcludeUserInputEvents);

//    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString replyData =  reply->readAll();

    reply->deleteLater();
    reply = nullptr;

    return replyData;
}


QByteArray HttpMsg::RequestGet(bool enablehttps,const QString &url)
{
    QNetworkAccessManager qnam;
    const QUrl aurl(url);
    QNetworkRequest qnr( aurl );

    if(enablehttps)
    {
        QSslConfiguration config = qnr.sslConfiguration();
        config.setPeerVerifyMode(QSslSocket::VerifyNone);
        config.setProtocol(QSsl::TlsV1_3);
        qnr.setSslConfiguration(config);
    }

    QNetworkReply *reply = qnam.get( qnr );

    QEventLoop eventloop;
    connect( reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
    eventloop.exec( QEventLoop::ExcludeUserInputEvents);

    QByteArray result=reply->readAll();

    reply->deleteLater();
    reply = nullptr;

    return result;
}




