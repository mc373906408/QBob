#ifndef SCREENCAPTURE_H
#define SCREENCAPTURE_H

#include <QObject>
#include <QPixmap>

class ScreenCapture : public QObject
{
    Q_OBJECT
public:
    static ScreenCapture& getInstance();


private:
    ScreenCapture();

    //删掉定义，防止后门注入
    ScreenCapture(const ScreenCapture &sg) =delete ;
    ScreenCapture &operator=(const ScreenCapture &sg)=delete ;

    /**
     * @brief allScreenshot 截取所有桌面，并拼接为一张图片
     * @return
     */
    void allScreenshot();

private:
    QPixmap m_final; // 屏幕图片
signals:
    void sgOpenNewWindow();
    void sgCloseWindow();
};

#endif // SCREENCAPTURE_H
