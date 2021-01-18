#include "ScreenCapture.h"
#include <QGuiApplication>
#include <QPainter>
#include <QScreen>
#include <QJsonObject>
#include <QJsonDocument>


ScreenCapture &ScreenCapture::getInstance()
{
    static ScreenCapture instance;
    return instance;
}

void ScreenCapture::startScreenshot()
{
    /*截取所有屏幕*/
    allScreenshot();
    /*打开新窗口*/
    openScreenshotWindow();
    /*设置图片*/
    m_pixmapProvider->setScreenshot(m_screenshot);
    emit sgRefeshPixmap();
}

ScreenCapture::ScreenCapture()
{
    m_pixmapProvider=new PixmapProvider();
}

ScreenCapture::~ScreenCapture()
{
    closeScreenshotWindow();
}

void ScreenCapture::allScreenshot()
{
    auto screens = QGuiApplication::screens();
    if(screens.isEmpty()){
        return;
    }

    QList<QPixmap> scrs;
    int w = 0, h = 0, p = 0;
    foreach (auto scr, screens) {
        /*获取窗口起点位置，左上窗口的左上角就是起点*/
        if(scr->geometry().topLeft().x()<m_startPoint.x()){
            m_startPoint=scr->geometry().topLeft();
        }else if(scr->geometry().topLeft().y()<m_startPoint.y()){
            m_startPoint=scr->geometry().topLeft();
        }
        QPixmap pix = scr->grabWindow(0);
        w += static_cast<int>(pix.width()/pix.devicePixelRatio());
        h += static_cast<int>(pix.height()/pix.devicePixelRatio());
        /*TODO 这里需要做排序，目前这里有问题*/
        scrs << pix;
    }
    m_screenshot=QPixmap(w, h);
    QPainter painter(&m_screenshot);
    m_screenshot.fill(Qt::black);
    foreach (auto scr, scrs) {
        painter.drawPixmap(QPoint(p, 0), scr);
        p += static_cast<int>(scr.width()/scr.devicePixelRatio());
    }
    return;
}

void ScreenCapture::openScreenshotWindow()
{
    closeScreenshotWindow();
    QJsonObject json;
    json["objectName"]=m_screenshotWindow;
    QRect rect=m_screenshot.rect();
    json["x"]=m_startPoint.x();
    json["y"]=m_startPoint.y();
    json["minimumWidth"]=rect.width();
    json["minimumHeight"]=rect.height();
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
