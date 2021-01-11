#ifndef HTTPMSG_H
#define HTTPMSG_H

#include <QObject>
#include <QDebug>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>


class HttpMsgInterface;

class HttpMsg:public QObject
{
    Q_OBJECT
public:
    static HttpMsg& getInstance();

//    QString RequestPostForm(bool enablehttps,const QString &url, const QByteArray &data);

    /**
     * @brief requestGet Get请求
     * @param url
     * @return
     */
    QString requestGet(const QString &url);

    /**
     * @brief addObject  如果需要回调，就加入列表
     * @param obj
     */
    void addObject(HttpMsgInterface* obj);

    /**
     * @brief delObject  删掉回调
     * @param obj
     */
    void delObject(HttpMsgInterface* obj);

    /**
     * @brief delObject 重载，清理所有回调（应该不会调吧）
     */
    void delObject();

private slots:

private:
    HttpMsg();
    ~HttpMsg();

    //删掉定义，防止后门注入
    HttpMsg(const HttpMsg &sg) =delete ;
    HttpMsg &operator=(const HttpMsg &sg)=delete ;

private:
    QNetworkAccessManager *m_manager;

    QList<HttpMsgInterface*> m_InterfaceList;
};

#endif
