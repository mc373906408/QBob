QT += quick quickwidgets core network

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += 3rd/spdlog/include

HEADERS += \
        HttpMsg/HttpMsg.h \
        log/TSpdlog.h \
        log/TSpdlogAssistant.h \
        log/HashList.h \
        TranslateAPI/TranslateEnum.h \
        TranslateAPI/Baidu/TextTranslation.h


SOURCES += \
        HttpMsg/HttpMsg.cpp \
        log/TSpdlog.cpp \
        log/TSpdlogAssistant.cpp \
        log/HashList.cpp \
        TranslateAPI/Baidu/TextTranslation.cpp \
        main.cpp

QMAKE_POST_LINK += xcopy $$system_path($$PWD/3rd/openssl/dll/*.dll) $$system_path($$OUT_PWD/release) /y &
