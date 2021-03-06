﻿#include "Tools.h"
#include <QRect>
#include <QGuiApplication>
#include <QScreen>

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

double Tools::getZoomFactor(int id)
{
#ifdef Q_OS_WIN32
    /* 可能存在的优化：使用静态变量存储值，并监听系统改变界面信号，重置该值 */
    QScreen* screen = QGuiApplication::screens()[id];
    int dpi = static_cast<int>(screen->logicalDotsPerInch());
    int devicePixel = static_cast<int>(screen->devicePixelRatio());

    if (devicePixel == 1) {
        if(dpi<=96){
            return 1.0;
        }else if(dpi<=120){
            return 1.25;
        }else if(dpi<=144){
            return 1.5;
        }else if(dpi<=168){
            return 1.75;
        }else if(dpi<=192){
            return 2.0;
        }else if(dpi>192){
            return 2.0;
        }
    }

    if (devicePixel == 2) {
        if(dpi<=72){
            return 1.5;
        }else if (dpi<=84){
            return 1.75;
        }else if(dpi<=96){
            return 2.0;
        }else if(dpi>96){
            return 2.0;
        }
    }
    return 1.0;
#else
    return 1.0;
#endif
}


int Tools::getMouseDesktopInt(const QPoint &mouse){
    auto lscreens = QGuiApplication::screens();
    int i =0;

    foreach(auto scr ,lscreens){
        int x1=scr->geometry().x();
        int y1=scr->geometry().y();
        int x2=scr->geometry().width()+x1;
        int y2=scr->geometry().height()+y1;
        if(mouse.x()>=x1&&mouse.x()<=x2)
        {
            if(mouse.y()>=y1&&mouse.y()<=y2)
            {
                return i;
            }
        }
        i++;
    }
    return 0;
}
