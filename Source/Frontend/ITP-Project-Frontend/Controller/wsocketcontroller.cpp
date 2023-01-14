// wSocketController.cpp

#include "wSocketController.h"
#include <QWebSocket>

wSocketController* wSocketController::instance = nullptr;

void wSocketController::connectToServer()
{
    WebSocketClient::getInstance().connectToServer(QUrl("ws://localhost:1214"));
}
