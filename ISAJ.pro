QT       += core gui
QT       += multimediawidgets
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    baiduocr.cpp \
    cameraset.cpp \
    fileop.cpp \
    isajdata.cpp \
    jsoncpp/jsoncpp.cpp \
    main.cpp \
    mainwin.cpp \
    ocrsystem.cpp \
    tableset.cpp

HEADERS += \
    IncludeItems.h \
    Includer.h \
    aip-cpp-sdk-4.16.7/body_analysis.h \
    aip-cpp-sdk-4.16.7/content_censor.h \
    aip-cpp-sdk-4.16.7/face.h \
    aip-cpp-sdk-4.16.7/image_censor.h \
    aip-cpp-sdk-4.16.7/image_classify.h \
    aip-cpp-sdk-4.16.7/image_process.h \
    aip-cpp-sdk-4.16.7/image_search.h \
    aip-cpp-sdk-4.16.7/kg.h \
    aip-cpp-sdk-4.16.7/machine_translation.h \
    aip-cpp-sdk-4.16.7/nlp.h \
    aip-cpp-sdk-4.16.7/ocr.h \
    aip-cpp-sdk-4.16.7/speech.h \
    aip-cpp-sdk-4.16.7/video_censor.h \
    aip-cpp-sdk-4.16.7/voice_censor.h \
    baiduocr.h \
    cameraset.h \
    fileop.h \
    isajdata.h \
    jsoncpp/json/json-forwards.h \
    jsoncpp/json/json.h \
    mainwin.h \
    ocrsystem.h \
    tableset.h

FORMS += \
    baiduocr.ui \
    mainwin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/../../../curl-7.68.0/curl-7.68.0/builds/libcurl-vc17-x64-debug-dll-ipv6-sspi-winssl/lib/ -llibcurl_debug

INCLUDEPATH += $$PWD/../../../curl-7.68.0/curl-7.68.0/builds/libcurl-vc17-x64-debug-dll-ipv6-sspi-winssl/include
DEPENDPATH += $$PWD/../../../curl-7.68.0/curl-7.68.0/builds/libcurl-vc17-x64-debug-dll-ipv6-sspi-winssl/include
