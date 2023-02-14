#include "menuwindow.h"

#include <QApplication>

#include "./utils/websocketclient.h"

#include "Views/view_finalscore.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MenuWindow w;

    WebSocketClient::getInstance();

    w.show();
    return a.exec();
}
