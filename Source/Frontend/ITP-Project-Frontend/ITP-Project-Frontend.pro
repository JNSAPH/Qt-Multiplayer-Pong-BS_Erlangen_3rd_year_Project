QT       += core gui
QT += widgets
QT += network
QT += websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/wsocketcontroller.cpp \
    Views/view_multiplayer.cpp \
    Views/view_waitinginqueue.cpp \
    gameManager/playermovementmanager.cpp \
    main.cpp \
    menuwindow.cpp \
    utils/HttpRequest.cpp \
    utils/websocketclient.cpp

HEADERS += \
    Controller/wsocketcontroller.h \
    Views/view_multiplayer.h \
    Views/view_waitinginqueue.h \
    gameManager/playermovementmanager.h \
    menuwindow.h \
    utils/HttpRequest.h \
    utils/websocketclient.h

FORMS += \
    Views/view_multiplayer.ui \
    Views/view_waitinginqueue.ui \
    menuwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
