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


    QQuickView engine;
    /*将自身注册到qml中*/
    engine.rootContext()->setContextProperty("cppWindow",&engine);

    /*将截图模块注册到qml中*/
    engine.rootContext()->setContextProperty("cppScreenCapture",&ScreenCapture::getInstance());


    engine.setSource(QUrl("qrc:/main.qml"));
    engine.show();

    return app.exec();
}
