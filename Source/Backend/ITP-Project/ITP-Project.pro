QT -= gui

CONFIG += c++17 console
QT += network
QT += sql
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        routes/httptestroute.cpp \
        routes/jsontestroute.cpp \
        utils/jsonutils.cpp \
        utils/mariadb.cpp \
        utils/ws_utils.cpp \
        ws/webserver.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    routes/httptestroute.h \
    routes/iroutehandler.h \
    routes/jsontestroute.h \
    utils/jsonutils.h \
    utils/mariadb.h \
    utils/ws_utils.h \
    ws/webserver.h
