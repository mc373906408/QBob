#ifndef HTTPMSG_H
#define HTTPMSG_H

#include <QObject>
#include <QDebug>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>


class HttpMsg:public QObject
{
    Q_OBJECT
public:
    static HttpMsg& getInstance();

    QString RequestPostForm(bool enablehttps,const QString &url, const QByteArray &data);

    /**
     * @brief RequestGet 从http接口中获取
     * @param urlSuffix http后缀
     * @param seturl http前缀 https://wb2.fudaojun.com/
     * @return
     */
    QByteArray RequestGet(bool enablehttps,const QString &url);


public slots:
private:
    HttpMsg();
    ~HttpMsg();

    //删掉定义，防止后门注入
    HttpMsg(const HttpMsg &sg) =delete ;
    HttpMsg &operator=(const HttpMsg &sg)=delete ;

};

#endif
