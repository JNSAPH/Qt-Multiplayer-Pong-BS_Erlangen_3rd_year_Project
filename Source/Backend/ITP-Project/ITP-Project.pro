QT -= gui

CONFIG += c++17 console
QT += network \
    widgets
QT += sql
CONFIG -= app_bundle

QT += websockets
QT += core5compat



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Pong/ball.cpp \
        Pong/game.cpp \
        Pong/paddle.cpp \
        gameManager/playercommunicationmanager.cpp \
        gameManager/queuemanager.cpp \
        main.cpp \
        routes/GetScoreRoute.cpp \
        routes/SetNameRoute.cpp \
        socket/websocketserver.cpp \
        utils/jsonutils.cpp \
        utils/logs.cpp \
        utils/mariadb.cpp \
        utils/score.cpp \
        utils/ws_utils.cpp \
        ws/webserver.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Pong/ball.h \
    Pong/game.h \
    Pong/paddle.h \
    gameManager/playercommunicationmanager.h \
    gameManager/queuemanager.h \
    routes/GetScoreRoute.h \
    routes/SetNameRoute.h \
    routes/iroutehandler.h \
    socket/websocketserver.h \
    utils/jsonutils.h \
    utils/logs.h \
    utils/mariadb.h \
    utils/score.h \
    utils/ws_utils.h \
    ws/webserver.h
