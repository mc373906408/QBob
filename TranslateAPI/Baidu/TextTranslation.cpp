#include "TextTranslation.h"
#include <QRandomGenerator>
#include <QCryptographicHash>
#include "HttpMsg/HttpMsg.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

TextTranslation::TextTranslation(QString appID, QString secretKey)
{
    m_appID=appID;
    m_secretKey=secretKey;
}

QString TextTranslation::getTranslation(const QString &q, const QString &fromLang, const QString &toLang)
{
    int salt=QRandomGenerator::global()->bounded(32768, 65536);
    QString sign=m_appID+q+QString::number(salt)+m_secretKey;
    sign=QCryptographicHash::hash(sign.toLatin1(),QCryptographicHash::Md5).toHex();
    QString url=QString("https://api.fanyi.baidu.com/api/trans/vip/translate?q=%1&from=%2&to=%3&appid=%4&salt=%5&sign=%6")
            .arg(q).arg(fromLang).arg(toLang).arg(m_appID).arg(salt).arg(sign);
    QByteArray result=HttpMsg::getInstance().RequestGet(true,url);
    QJsonDocument document=QJsonDocument::fromJson(result);
    QJsonObject object=document.object();
    QJsonObject trans_result=object.value("trans_result")[0].toObject();
    return trans_result.value("dst").toString();
}
