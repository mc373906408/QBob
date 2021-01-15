#include "Tools.h"

Tools::Tools()
{

}

Tools& Tools::getInstance()
{
    static Tools instance;
    return instance;
}

QByteArray Tools::imageToBase64(const QImage &image)
{
    return QByteArray();
}
