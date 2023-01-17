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
    Views/view_multiplayer.cpp \
    Views/view_waitinginqueue.cpp \
    gameManager/gamestate.cpp \
    gameManager/playercommunicationmanager.cpp \
    gameManager/playermanager.cpp \
    main.cpp \
    menuwindow.cpp \
    utils/HttpRequest.cpp \
    utils/websocketclient.cpp

HEADERS += \
    Views/view_multiplayer.h \
    Views/view_waitinginqueue.h \
    gameManager/gamestate.h \
    gameManager/playercommunicationmanager.h \
    gameManager/playermanager.h \
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

RESOURCES += \
    resource.qrc

DISTFILES +=
