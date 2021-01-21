#ifndef SCREENCAPTURE_H
#define SCREENCAPTURE_H

#include <QObject>
#include <QQuickImageProvider>
#include <QPixmap>

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

    /**
     * @brief getPixmapProvider 返回m_pixmapProvider指针
     * @return
     */
    PixmapProvider *getPixmapProvider();

    /**
     * @brief startScreenshot 启动截屏
     * @param id
     */
    void startScreenshot(const int &id);

    /**
     * @brief stopScreenshot 停止截图
     */
    void stopScreenshot();
private:
    ScreenCapture();
    ~ScreenCapture();

    //删掉定义，防止后门注入
    ScreenCapture(const ScreenCapture &sg) =delete ;
    ScreenCapture &operator=(const ScreenCapture &sg)=delete ;


    QPixmap screenshot(const int &id);

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
signals:
    void sgOpenWindow(QObject *parent,const QString &json);
    void sgCloseWindow(const QString &objectName);
    void sgRefeshPixmap();
};

#endif // SCREENCAPTURE_H
