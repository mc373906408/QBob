#ifndef TEXTTRANSLATION_H
#define TEXTTRANSLATION_H

#include <QObject>
#include "HttpMsg/HttpMsgInterface.h"

class TextTranslation:public QObject,public HttpMsgInterface
{
    Q_OBJECT
public:
    TextTranslation(QString appID,QString secretKey);
    ~TextTranslation();

    /*执行翻译*/
    QString getTranslation(const QString &q,const QString &fromLang,const QString &toLang);
private:
    virtual void handleCallback(const QString &id,const QByteArray &replyData);
private:
    QString m_appID;
    QString m_secretKey;
    QStringList m_requestUrl;
};

#endif
