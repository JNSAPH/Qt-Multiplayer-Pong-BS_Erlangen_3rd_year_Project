#include "view_multiplayer.h"
#include "ui_view_multiplayer.h"

#include "utils/websocketclient.h"

view_multiplayer::view_multiplayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::view_multiplayer)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(680, 559));

    this->setWindowTitle("Multiplayer - Pong (ITP)");

    m_playerManager = &PlayerManager::getInstance();

    // Start Timer for movement
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &view_multiplayer::movePlayer);
    timer->start(1);
}

view_multiplayer::~view_multiplayer()
{
    delete ui;
}

void view_multiplayer::setPaddleColor() {
    if(m_playerManager->getPlayerNumber() == 1) {
        // set paddle img_paddle1 to resource paddle_player
        ui->img_paddle1->setPixmap(QPixmap(":/resources/bg/resources/paddle_player.png"));
    } else {
        // set paddle img_paddle2 to resource paddle_player
        ui->img_paddle2->setPixmap(QPixmap(":/resources/bg/resources/paddle_player.png"));
    }
}

void view_multiplayer::updatePlayingField() {
    m_state = &GameState::getInstance();

    ui->img_ball->setGeometry(m_state->getBall().x, m_state->getBall().y, m_state->getBall().diameter, m_state->getBall().diameter);
    ui->img_paddle1->setGeometry(m_state->getPaddle1().x, m_state->getPaddle1().y, m_state->getPaddle1().width, m_state->getPaddle1().height);
    ui->img_paddle2->setGeometry(m_state->getPaddle2().x, m_state->getPaddle2().y, m_state->getPaddle2().width, m_state->getPaddle2().height);

    ui->score_p1->setText(QString::number(m_state->getScore1()));
    ui->score_p2->setText(QString::number(m_state->getScore2()));
}

void view_multiplayer::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        case Qt::Key_W: UP_pressed = true; break;
        case Qt::Key_S: DOWN_pressed = true; break;
        case Qt::Key_Up: UP_pressed = true; break;
        case Qt::Key_Down: DOWN_pressed = true; break;
    }
}

void view_multiplayer::movePlayer() {
    QJsonObject jsonObject;
    jsonObject.insert("code", 110);
    jsonObject.insert("player", m_playerManager->getPlayerNumber());

    if(UP_pressed)
        jsonObject.insert("action", "up");
    else if(DOWN_pressed)
        jsonObject.insert("action", "down");

    if(UP_pressed || DOWN_pressed) {
        QJsonDocument jsonDoc(jsonObject);
        QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);
        WebSocketClient::getInstance().sendMessage(jsonString);
        UP_pressed = false;
        DOWN_pressed = false;
    }


}

