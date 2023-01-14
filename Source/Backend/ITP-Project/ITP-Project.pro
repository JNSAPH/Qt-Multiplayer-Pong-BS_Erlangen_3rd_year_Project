QT -= gui

CONFIG += c++17 console
QT += network \
    widgets
QT += sql
CONFIG -= app_bundle

QT += websockets



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        gameManager/gamestate.cpp \
        gameManager/playermovementmanager.cpp \
        gameManager/queuemanager.cpp \
        main.cpp \
        routes/httptestroute.cpp \
        routes/jsontestroute.cpp \
        routes/requestqueueroute.cpp \
        socket/websocketserver.cpp \
        utils/jsonutils.cpp \
        utils/mariadb.cpp \
        utils/ws_utils.cpp \
        ws/webserver.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    gameManager/gamestate.h \
    gameManager/playermovementmanager.h \
    gameManager/queuemanager.h \
    routes/httptestroute.h \
    routes/iroutehandler.h \
    routes/jsontestroute.h \
    routes/requestqueueroute.h \
    socket/websocketserver.h \
    utils/jsonutils.h \
    utils/mariadb.h \
    utils/ws_utils.h \
    ws/webserver.h
