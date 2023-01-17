#include "view_multiplayer.h"
#include "ui_view_multiplayer.h"

#include "utils/websocketclient.h"

view_multiplayer::view_multiplayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::view_multiplayer)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(680, 540));

    m_playerManager = &PlayerManager::getInstance();
}

view_multiplayer::~view_multiplayer()
{
    delete ui;
}

void view_multiplayer::updatePlayingField() {
    m_state = &GameState::getInstance();

    // Print Ball
    qDebug() << "Ball Radius" << m_state->getBall().radius;
    qDebug() << "Ball X: " << m_state->getBall().x << "Ball Y: " << m_state->getBall().y;
    qDebug() << "Ball Velocity X: " << m_state->getBall().vx << "Ball Velocity Y: " << m_state->getBall().vy;

    ui->btnBall->setGeometry(m_state->getBall().x, m_state->getBall().y, m_state->getBall().radius, m_state->getBall().radius);
    ui->btnPaddle1->setGeometry(m_state->getPaddle1().x, m_state->getPaddle1().y, m_state->getPaddle1().width, m_state->getPaddle1().height);
    ui->btnPaddle2->setGeometry(m_state->getPaddle2().x, m_state->getPaddle2().y, m_state->getPaddle2().width, m_state->getPaddle2().height);

    ui->score_p1->setText(QString::number(m_state->getScore1()));
    ui->score_p2->setText(QString::number(m_state->getScore2()));

    // Print Paddle 1
    qDebug() << "Paddle 1 X: " << m_state->getPaddle1().x << "Paddle 1 Y: " << m_state->getPaddle1().y;
    qDebug() << "Paddle 1 Width: " << m_state->getPaddle1().width << "Paddle 1 Height: " << m_state->getPaddle1().height;

    // Print Paddle 2
    qDebug() << "Paddle 2 X: " << m_state->getPaddle2().x << "Paddle 2 Y: " << m_state->getPaddle2().y;
    qDebug() << "Paddle 2 Width: " << m_state->getPaddle2().width << "Paddle 2 Height: " << m_state->getPaddle2().height;

    // Print Score
    qDebug() << "Score 1: " << m_state->getScore1() << "Score 2: " << m_state->getScore2();
}
