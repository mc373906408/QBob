#ifndef TEXTTRANSLATION_H
#define TEXTTRANSLATION_H

#include <QObject>

class TextTranslation:public QObject
{
    Q_OBJECT
public:
    TextTranslation(QString appID,QString secretKey);

    /*执行翻译*/
    QString getTranslation(const QString &q,const QString &fromLang,const QString &toLang);
private:
    QString m_appID;
    QString m_secretKey;
};

#endif
