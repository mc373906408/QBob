#include <QApplication>
#include <QQuickView>
#include <QQmlContext>
#include "TranslateAPI/TranslateEnum.h"
#include "TranslateAPI/Baidu/TextTranslation.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication app(argc, argv);

    TextTranslation m_TextTranslation("20201020000594558","MB7lLwBLXBBL9I6iWje8");
    m_TextTranslation.getTranslation("Banana",Translate_Language_AUTO,Translate_Language_ZH);


    QQuickView engine;
    /*将自身注册到qml中*/
    engine.rootContext()->setContextProperty("cppWindow",&engine);


    engine.setSource(QUrl("qrc:/main.qml"));
    engine.show();

    return app.exec();
}
