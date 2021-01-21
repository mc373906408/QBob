#ifndef SCREENCAPTURE_H
#define SCREENCAPTURE_H

#include <QObject>
#include <QQuickImageProvider>
#include <QPixmap>

#include <Windows.h>
#include <dxgi1_6.h>
#include <d3d11.h>

/*向QML中发送图像*/
class PixmapProvider : public QQuickImageProvider
{
public:
    PixmapProvider();

    void setScreenshot(const QPixmap &screenshot);
private:
    virtual QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
    QPixmap m_screenshot;

};

class ScreenCapture : public QObject
{
    Q_OBJECT
public:
    static ScreenCapture& getInstance();

    void startScreenshot();
    /**
     * @brief getPixmapProvider 返回m_pixmapProvider指针
     * @return
     */
    PixmapProvider *getPixmapProvider();
private:
    ScreenCapture();
    ~ScreenCapture();

    //删掉定义，防止后门注入
    ScreenCapture(const ScreenCapture &sg) =delete ;
    ScreenCapture &operator=(const ScreenCapture &sg)=delete ;

    /**
     * @brief dxgiInit 初始化dxgi接口
     * @return
     */
    bool dxgiInit();

    /**
     * @brief allScreenshot 截取所有桌面，并拼接为一张图片
     * @return
     */
    QPixmap allScreenshot();

    QPixmap copyToImage(IDXGIResource *res);

    /**
     * @brief openScreenshotWindow 创建截图编辑窗口
     */
    void openScreenshotWindow(const QPixmap &screenshot);

    /**
     * @brief closeScreenshotWindow 关闭截图编辑窗口
     */
    void closeScreenshotWindow();



private:
    QPoint m_startPoint=QPoint(0,0); // 创建截屏窗口的起点坐标
    QString m_screenshotWindow="screenshotWindow";  //窗口的objectName
    bool m_isOpenWindow=false; // 是否打开截图窗口
    PixmapProvider *m_pixmapProvider=nullptr;
    IDXGIOutputDuplication *m_duplication=nullptr;
    ID3D11Device *m_d3dDevice=nullptr;
    ID3D11DeviceContext *m_d3dContext=nullptr;
signals:
    void sgOpenWindow(QObject *parent,const QString &json);
    void sgCloseWindow(const QString &objectName);
    void sgRefeshPixmap();
};

#endif // SCREENCAPTURE_H
