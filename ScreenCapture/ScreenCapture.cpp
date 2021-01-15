#include "ScreenCapture.h"
#include <QGuiApplication>
#include <QPainter>
#include <QScreen>

ScreenCapture &ScreenCapture::getInstance()
{
    static ScreenCapture instance;
    return instance;
}

ScreenCapture::ScreenCapture()
{

}

void ScreenCapture::allScreenshot()
{
#ifdef Q_OS_WIN
    auto screens = QGuiApplication::screens();
    QList<QPixmap> scrs;
    int w = 0, h = 0, p = 0;
    QList<qreal> dotsPerInch;
    foreach (auto scr, screens) {
        QPixmap pix = scr->grabWindow(0);
        w += static_cast<int>(pix.width()/pix.devicePixelRatio());
        if (h < pix.height()) h = static_cast<int>(pix.height()/pix.devicePixelRatio());
        scrs << pix;
        dotsPerInch<<pix.devicePixelRatio();
    }
    QPixmap final(w, h);
    QPainter painter(&final);
    final.fill(Qt::black);
    foreach (auto scr, scrs) {
        painter.drawPixmap(QPoint(p, 0), scr);
        p += static_cast<int>(scr.width()/dotsPerInch.first());
    }

#elif defined Q_OS_MAC
    auto screens=QGuiApplication::screens();
    QPixmap final=screens.first()->grabWindow(0);
#endif
    return;
}
