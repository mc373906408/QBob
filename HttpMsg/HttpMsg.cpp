/*  Qt6 默认启动HTTP/2，如果只能使用HTTP/1.1，
 *  则可针对新的网络请求将属性'Http2AllowedAttribute'设置为'false'
 */
#include "HttpMsg.h"

#include <QMutex>
#include <QRegularExpression>

#include "HttpMsgInterface.h"

static QMutex mutex_InterfaceList;

HttpMsg& HttpMsg::getInstance()
{
    static HttpMsg instance;
    return instance;
}

HttpMsg::HttpMsg()
{
    m_manager= new QNetworkAccessManager(this);
    /*异步获取http请求回调，这里不用再做阻塞，当需要回调时，继承纯虚接口*/
    connect(m_manager,&QNetworkAccessManager::finished,[&](QNetworkReply *reply){
        QString id=reply->url().toString(); //url作为唯一id
        QByteArray replyData;
        if(reply->error()==QNetworkReply::NoError){
            /*请求成功*/
            replyData=reply->readAll(); //回调数据
        }else{
            /*TODO 请求失败*/
            qDebug()<<reply->error();
            replyData="ERROR";
        }
        /*广播信息*/
        QMutexLocker locker(&mutex_InterfaceList);
        foreach(auto base,m_InterfaceList){
            base->handleCallback(id,replyData);
        }
    });
}
HttpMsg::~HttpMsg()
{
    m_manager->deleteLater();
}


QString HttpMsg::requestPostForm(const QString &url, const QByteArray &data)
{

    const QUrl aurl(url);
    QNetworkRequest qnr( aurl );

    /*启动tls*/
    if(url.contains(QRegularExpression("^https://")))
    {
        QSslConfiguration config = qnr.sslConfiguration();
        config.setProtocol(QSsl::SecureProtocols);  //自动协商
        qnr.setSslConfiguration(config);
    }

    qnr.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    qnr.setHeader(QNetworkRequest::ContentLengthHeader,data.size());

    m_manager->post(qnr,data);

    /*返回url 作为唯一ID*/
    return qnr.url().toString();
}


QString HttpMsg::requestGet(const QString &url)
{
    const QUrl aurl(url);
    QNetworkRequest qnr( aurl );

    /*启动tls*/
    if(url.contains(QRegularExpression("^https://")))
    {
        QSslConfiguration config = qnr.sslConfiguration();
        config.setProtocol(QSsl::SecureProtocols);  //自动协商
        qnr.setSslConfiguration(config);
    }

    m_manager->get(qnr);

    /*返回url 作为唯一ID*/
    return qnr.url().toString();
}

void HttpMsg::addObject(HttpMsgInterface *obj)
{
    QMutexLocker locker(&mutex_InterfaceList);
    m_InterfaceList.push_back(obj);
}

void HttpMsg::delObject(HttpMsgInterface *obj)
{
    QMutexLocker locker(&mutex_InterfaceList);
    m_InterfaceList.removeOne(obj);
}

void HttpMsg::delObject()
{
    QMutexLocker locker(&mutex_InterfaceList);
    m_InterfaceList.clear();
}






