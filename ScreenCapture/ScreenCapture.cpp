#include "ScreenCapture.h"
#include <QGuiApplication>
#include <QPainter>
#include <QScreen>
#include <QJsonObject>
#include <QJsonDocument>

#include "Tools/Tools.h"




ScreenCapture &ScreenCapture::getInstance()
{
    static ScreenCapture instance;
    return instance;
}

void ScreenCapture::startScreenshot(const int &id)
{
    /*截取所有屏幕*/
    QPixmap screenshotPix=screenshot(id);
    /*打开新窗口*/
    openScreenshotWindow(screenshotPix);
    /*设置图片*/
    m_pixmapProvider->setScreenshot(screenshotPix);
    emit sgRefeshPixmap();
}

void ScreenCapture::stopScreenshot()
{
    closeScreenshotWindow();
}

ScreenCapture::ScreenCapture()
{
    m_pixmapProvider=new PixmapProvider();
}

ScreenCapture::~ScreenCapture()
{
    closeScreenshotWindow();
}

QPixmap ScreenCapture::screenshot(const int &id)
{
        auto screens = QGuiApplication::screens();
        if(screens.isEmpty()){
            return QPixmap();
        }

//        QList<QPixmap> scrs;
//        int w = 0, h = 0, p = 0;
//        foreach (auto scr, screens) {
//            /*获取窗口起点位置，左上窗口的左上角就是起点*/
//            if(scr->geometry().topLeft().x()<m_startPoint.x()){
//                m_startPoint=scr->geometry().topLeft();
//            }else if(scr->geometry().topLeft().y()<m_startPoint.y()){
//                m_startPoint=scr->geometry().topLeft();
//            }
//            QPixmap pix = scr->grabWindow(0);
//            w += static_cast<int>(pix.width()/pix.devicePixelRatio());
//            h += static_cast<int>(pix.height()/pix.devicePixelRatio());
//            /*TODO 这里需要做排序，目前这里有问题*/
//            scrs << pix;
//        }
//        m_screenshot=QPixmap(w, h);
//        QPainter painter(&m_screenshot);
//        m_screenshot.fill(Qt::black);
//        foreach (auto scr, scrs) {
//            painter.drawPixmap(QPoint(p, 0), scr);
//            p += static_cast<int>(scr.width()/scr.devicePixelRatio());
//        }
//        return;

        m_startPoint=screens[id]->geometry().topLeft();
        return screens[id]->grabWindow(0);

}

void ScreenCapture::openScreenshotWindow(const QPixmap &screenshot)
{
    closeScreenshotWindow();
    QJsonObject json;
    json["objectName"]=m_screenshotWindow;
    QRect rect=screenshot.rect();
    json["x"]=m_startPoint.x();
    json["y"]=m_startPoint.y();
    json["minimumWidth"]=rect.width()/Tools::getInstance().getZoomFactor();
    json["minimumHeight"]=rect.height()/Tools::getInstance().getZoomFactor();
    emit sgOpenWindow(nullptr,QJsonDocument(json).toJson());
    m_isOpenWindow=true;
}

void ScreenCapture::closeScreenshotWindow()
{
    if(m_isOpenWindow){
        emit sgCloseWindow(m_screenshotWindow);
        m_isOpenWindow=false;
    }
}

PixmapProvider *ScreenCapture::getPixmapProvider()
{
    return m_pixmapProvider;
}

PixmapProvider::PixmapProvider():QQuickImageProvider(QQuickImageProvider::Pixmap)
{

}

void PixmapProvider::setScreenshot(const QPixmap &screenshot)
{
    m_screenshot=screenshot;
}

QPixmap PixmapProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(id)
    Q_UNUSED(size)
    Q_UNUSED(requestedSize)
    return m_screenshot;
}
