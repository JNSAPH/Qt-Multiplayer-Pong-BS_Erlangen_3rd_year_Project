#include "view_waitinginqueue.h"
#include "ui_view_waitinginqueue.h"

view_waitingInQueue::view_waitingInQueue(QWidget *parent) : QDialog(parent), ui(new Ui::view_waitingInQueue)
{
    ui->setupUi(this);

    // Connect to Websocket
    WebSocketClient::getInstance().connectToServer(QUrl("ws://localhost:1214"));

}

view_waitingInQueue::~view_waitingInQueue()
{
    delete ui;
}
