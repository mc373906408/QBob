﻿# 最低版本号
cmake_minimum_required(VERSION 3.15)

# 项目信息
project(QBob 
    VERSION 0.0.1
    LANGUAGES CXX)


# Use folders in the resulting project files.
set_property(GLOBAL PROPERTY OS_FOLDERS ON)

# 设置ROOT目录
set(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

# 加载cmake子模块
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_ROOT}/cmake")

# 自动添加CMAKE_CURRENT_BINARY_DIR和CMAKE_CURRENT_SOURCE_DIR到当前处理的CMakeLists.txt
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 设置自动生成ui.h文件, AUTOUIC打开可以省去QT5_WRAP_UI命令
set(CMAKE_AUTOUIC ON)
# 设置自动生成moc文件,AUTOMOC打开可以省去QT5_WRAP_CPP命令
set(CMAKE_AUTOMOC ON)
# 将资源文件转化为二进制的rcc文件
set(CMAKE_AUTORCC ON)

# 指定C++版本号 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 指定qt编译版本6
set(QT_VERSION_MAJOR 6)

# 禁用QT5.15中弃用的C++API
add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0x050F00)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.


# 引入外部依赖包，同时需要修改target_link_libraries
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick QuickWidgets Network REQUIRED)


# 引入头文件路径
include_directories(3rd)
include_directories(3rd/qhook/include)
link_directories(3rd/qhook/lib)
include_directories(3rd/EasyLogger/include)
link_directories(3rd/EasyLogger/lib)

# 源文件  cpp\h\qrc\hpp\c
set(PROJECT_SOURCES
    main.cpp
    Qml/qml.qrc
    TranslateAPI/TranslateEnum.h
    TranslateAPI/Baidu/BaiduTranslation.h
    TranslateAPI/Baidu/BaiduTranslation.cpp
    Log/ThirdEasyLogger.cpp
    Log/ThirdEasyLogger.h
    HttpMsg/HttpMsg.cpp
    HttpMsg/HttpMsg.h
    HttpMsg/HttpMsgInterface.h
    TranslateAPI/Baidu/BaiduOCR.h
    TranslateAPI/Baidu/BaiduOCR.cpp
    Tools/Tools.h
    Tools/Tools.cpp
    Tools/WindowHook.h
    Tools/WindowHook.cpp
    ScreenCapture/ScreenCapture.h
    ScreenCapture/ScreenCapture.cpp
    )

# QT版本控制，不用动
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
        )
else()
    add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
        )
endif()

# 宏定义
target_compile_definitions(${PROJECT_NAME}
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)




# 将目标文件与库文件进行链接
target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::QuickWidgets
    Qt${QT_VERSION_MAJOR}::Network
    QHook user32
    EasyLogger
    pthreadVC2
    )


# 构造完成后执行
#add_custom_command(TARGET
#    POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy 3rd/openssl/dll/*.dll  )
