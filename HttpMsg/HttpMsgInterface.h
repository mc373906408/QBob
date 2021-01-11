#ifndef HTTPMSGINTERFACE_H
#define HTTPMSGINTERFACE_H

/* 纯虚类，做接口用
 */

#include <QString>

class HttpMsgInterface
{
public:
    virtual ~HttpMsgInterface()=default;

    virtual void handleCallback(const QString &id,const QByteArray &replyData)=0;
};

#endif // HTTPMSGINTERFACE_H
