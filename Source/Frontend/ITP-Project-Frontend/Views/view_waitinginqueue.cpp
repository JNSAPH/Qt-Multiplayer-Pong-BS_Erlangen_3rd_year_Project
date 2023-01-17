#include "view_waitinginqueue.h"
#include "ui_view_waitinginqueue.h"

view_waitingInQueue* view_waitingInQueue::m_instance = nullptr;

view_waitingInQueue* view_waitingInQueue::getInstance() {
    if (m_instance == nullptr) {
        m_instance = new view_waitingInQueue;
    }
    return m_instance;
}

view_waitingInQueue::view_waitingInQueue(QWidget *parent) : QDialog(parent), ui(new Ui::view_waitingInQueue)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(363, 117));
    this->setWindowTitle("Waiting for Players - Pong (ITP)");
    // Connect to Websocket
    WebSocketClient::getInstance().connectToServer(QUrl("ws://localhost:1214"));
}

void view_waitingInQueue::startGame() {
    // Create Multiplayer Window
    view_multiplayer* MultiplayerWindow = new view_multiplayer();
    //MultiplayerWindow->show();

    this->close();
}

view_waitingInQueue::~view_waitingInQueue()
{
    delete ui;
}
