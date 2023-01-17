#include "view_multiplayer.h"
#include "ui_view_multiplayer.h"

#include "utils/websocketclient.h"

view_multiplayer::view_multiplayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::view_multiplayer)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(680, 540));

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

    ui->img_ball->setGeometry(m_state->getBall().x, m_state->getBall().y, m_state->getBall().radius, m_state->getBall().radius);
    ui->img_paddle1->setGeometry(m_state->getPaddle1().x, m_state->getPaddle1().y, m_state->getPaddle1().width, m_state->getPaddle1().height);
    ui->img_paddle2->setGeometry(m_state->getPaddle2().x, m_state->getPaddle2().y, m_state->getPaddle2().width, m_state->getPaddle2().height);

    ui->score_p1->setText(QString::number(m_state->getScore1()));
    ui->score_p2->setText(QString::number(m_state->getScore2()));

    /*
    // Print Ball
    qDebug() << "Ball Radius" << m_state->getBall().radius;
    qDebug() << "Ball X: " << m_state->getBall().x << "Ball Y: " << m_state->getBall().y;
    qDebug() << "Ball Velocity X: " << m_state->getBall().vx << "Ball Velocity Y: " << m_state->getBall().vy;

    // Print Paddle 1
    qDebug() << "Paddle 1 X: " << m_state->getPaddle1().x << "Paddle 1 Y: " << m_state->getPaddle1().y;
    qDebug() << "Paddle 1 Width: " << m_state->getPaddle1().width << "Paddle 1 Height: " << m_state->getPaddle1().height;

    // Print Paddle 2
    qDebug() << "Paddle 2 X: " << m_state->getPaddle2().x << "Paddle 2 Y: " << m_state->getPaddle2().y;
    qDebug() << "Paddle 2 Width: " << m_state->getPaddle2().width << "Paddle 2 Height: " << m_state->getPaddle2().height;

    // Print Score
    qDebug() << "Score 1: " << m_state->getScore1() << "Score 2: " << m_state->getScore2();
    */
}

void view_multiplayer::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        case Qt::Key_W: UP_pressed = true; break;
        case Qt::Key_S: DOWN_pressed = true; break;
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

