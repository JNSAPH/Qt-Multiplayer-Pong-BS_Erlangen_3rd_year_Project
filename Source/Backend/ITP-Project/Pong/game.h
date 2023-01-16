#ifndef GAME_H
#define GAME_H

#include "Paddle.h"
#include "Ball.h"

#include <QObject>

#include <QJsonObject>
#include <QJsonDocument>
#include <QTimer>

#include "../socket/websocketserver.h"


class Game : public QObject
{
    Q_OBJECT
public:
    static Game& getInstance();
    void update();
    void start();
    void stop();
    void reset();
    void sendState();

    void movePaddle1Up();
    void movePaddle1Down();
    void movePaddle2Up();
    void movePaddle2Down();

    int getScore(int player);
    void setScore(int player, int score);


private:
    int m_paddleLeftX = 29;
    int m_paddleY = 230;
    int m_paddleRightX = 625;

private:
    Game();
    Game(Game const&) = delete;
    void operator=(Game const&) = delete;
    int m_score1;
    int m_score2;
    bool m_running;
    QTimer *m_timer;
    int m_playingFieldWidth;
    int m_playingFieldHeight;
    Paddle m_paddle1;
    Paddle m_paddle2;
    Ball m_ball;
    QJsonObject m_winnerBroadcast;

};

#endif // GAME_H
