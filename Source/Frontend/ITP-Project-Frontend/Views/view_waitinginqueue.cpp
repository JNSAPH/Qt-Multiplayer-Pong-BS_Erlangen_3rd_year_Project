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

    // Access the command-line arguments
    QStringList args = QCoreApplication::arguments();

    // Search for the "--ip" and "--ws_port" arguments
    for (int i = 1; i < args.size(); i++) {
        if (args.at(i) == "--ip" && i+1 < args.size()) {
            m_ip = args.at(i+1);
        } else if (args.at(i) == "--ws_port" && i+1 < args.size()) {
            m_port = args.at(i+1);
        }
    }

    qDebug() << args;

    // Connect to Websocket
    WebSocketClient::getInstance().connectToServer(QUrl("ws://" + m_ip + ":" + m_port));
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
