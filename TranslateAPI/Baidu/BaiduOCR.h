#ifndef BAIDUOCR_H
#define BAIDUOCR_H

#include <QObject>

class BaiduOCR : public QObject
{
    Q_OBJECT
public:
    explicit BaiduOCR(QObject *parent = nullptr);

signals:

};

#endif // BAIDUOCR_H
