QT       += core gui
QT       += multimediawidgets
QT       += multimedia
QT       += axcontainer

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

win32: LIBS += -L$$PWD/../../../curl-8.9.1/builds/libcurl-vc17-x64-release-dll-ipv6-sspi-schannel/lib/ -llibcurl

INCLUDEPATH += $$PWD/../../../curl-8.9.1/builds/libcurl-vc17-x64-release-dll-ipv6-sspi-schannel/include
DEPENDPATH += $$PWD/../../../curl-8.9.1/builds/libcurl-vc17-x64-release-dll-ipv6-sspi-schannel/include

RESOURCES += \
    IMGS.qrc
