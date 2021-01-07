# 最低版本号
cmake_minimum_required(VERSION 3.14)

# 项目信息
project(QBob 
        VERSION 0.0.1
        LANGUAGES CXX) 

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

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

# 引入外部依赖包，同时需要修改target_link_libraries
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick QuickWidgets Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick QuickWidgets Network REQUIRED)

# 引入头文件路径
include_directories(3rd)

# 源文件  cpp\h\qrc\hpp\c
set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        TranslateAPI/TranslateEnum.h
        TranslateAPI/Baidu/TextTranslation.h
        TranslateAPI/Baidu/TextTranslation.cpp
        Log/HashList.cpp
        Log/HashList.h
        Log/TSpdlog.cpp
        Log/TSpdlog.h
        Log/TSpdlogAssistant.cpp
        Log/TSpdlogAssistant.h
        HttpMsg/HttpMsg.cpp
        HttpMsg/HttpMsg.h

        )

# QT版本控制，不用动
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(${PROJECT_NAME}
          ${PROJECT_SOURCES}
        )
    endif()
endif()

# 宏定义
target_compile_definitions(${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
# 将目标文件与库文件进行链接
target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt${QT_VERSION_MAJOR}::Core
          Qt${QT_VERSION_MAJOR}::Quick
          Qt${QT_VERSION_MAJOR}::QuickWidgets
          Qt${QT_VERSION_MAJOR}::Network)

# 构造完成后执行
#add_custom_command(TARGET
#    POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy 3rd/openssl/dll/*.dll  )
