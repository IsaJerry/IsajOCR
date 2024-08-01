QT       += core gui
QT       += multimediawidgets
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cameraset.cpp \
    fileop.cpp \
    isajdata.cpp \
    main.cpp \
    mainwin.cpp \
    ocrsystem.cpp \
    tableset.cpp

HEADERS += \
    IncludeItems.h \
    Includer.h \
    cameraset.h \
    fileop.h \
    isajdata.h \
    mainwin.h \
    ocrsystem.h \
    tableset.h

FORMS += \
    mainwin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../python/libs/ -lpython312
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../python/libs/ -lpython312d

INCLUDEPATH += $$PWD/../../../python/include
DEPENDPATH += $$PWD/../../../python/include

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../python/libs/libpython312.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../python/libs/libpython312d.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../python/libs/python312.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../python/libs/python312d.lib
