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
    jsoncpp.cpp \
    main.cpp \
    mainwin.cpp \
    ocrsystem.cpp \
    preset.cpp \
    tableset.cpp

HEADERS += \
    ISAJDataNames.h \
    IncludeItems.h \
    Includer.h \
    baiduocr.h \
    cameraset.h \
    fileop.h \
    isajdata.h \
    json/json-forwards.h \
    json/json.h \
    mainwin.h \
    ocrsystem.h \
    preset.h \
    tableset.h

FORMS += \
    baiduocr.ui \
    mainwin.ui \
    preset.ui

RC_ICONS = Sources\icon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



win32: LIBS += -L$$PWD/../../../curl-7.68.0/curl-7.68.0/builds/libcurl-vc17-x64-debug-dll-ipv6-sspi-winssl/lib/ -llibcurl_debug

INCLUDEPATH += $$PWD/../../../curl-7.68.0/curl-7.68.0/builds/libcurl-vc17-x64-debug-dll-ipv6-sspi-winssl/include
DEPENDPATH += $$PWD/../../../curl-7.68.0/curl-7.68.0/builds/libcurl-vc17-x64-debug-dll-ipv6-sspi-winssl/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../curl-7.68.0/curl-7.68.0/builds/libcurl-vc17-x64-debug-dll-ipv6-sspi-winssl/lib/libcurl_debug.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../../curl-7.68.0/curl-7.68.0/builds/libcurl-vc17-x64-debug-dll-ipv6-sspi-winssl/lib/liblibcurl_debug.a
