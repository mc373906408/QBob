#include <QApplication>
#include <QQuickView>
#include <QQmlContext>
#include "TranslateAPI/TranslateEnum.h"
#include "TranslateAPI/Baidu/BaiduTranslation.h"
#include "ScreenCapture/ScreenCapture.h"

int main(int argc, char *argv[])
{
    /*QT6现在默认支持并开启highDPI https://doc.qt.io/qt-6/highdpi.html*/
    QApplication app(argc, argv);

    BaiduTranslation m_TextTranslation("20201020000594558","MB7lLwBLXBBL9I6iWje8");
    m_TextTranslation.getTranslation("Banana",Translate_Language_AUTO,Translate_Language_ZH);


    QQuickView view;
    QQmlEngine *engine=view.engine();
    /*将自身注册到qml中*/
    view.rootContext()->setContextProperty("cppWindow",&view);

    /*将截图模块注册到qml中*/
    view.rootContext()->setContextProperty("cppScreenCapture",&ScreenCapture::getInstance());

    /*将截图后的图片加载到qml中*/
    engine->addImageProvider("screenshot",ScreenCapture::getInstance().getPixmapProvider());

    view.setSource(QUrl("qrc:/main.qml"));
//    view.show();

    ScreenCapture::getInstance().startScreenshot();

    int rv=app.exec();

    return rv;
}
