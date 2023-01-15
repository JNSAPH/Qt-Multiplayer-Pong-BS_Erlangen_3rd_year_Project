#ifndef GAME_H
#define GAME_H

#include "Paddle.h"
#include "Ball.h"

#include <QJsonObject>
#include <QJsonDocument>
#include "../socket/websocketserver.h"


class Game
{
public:
    static Game& getInstance();
    void update();
    void start();
    void stop();
    void reset();
    void sendState();

    int getScore(int player);
    void setScore(int player, int score);

private:
    Game();
    Game(Game const&) = delete;
    void operator=(Game const&) = delete;
    Paddle m_paddle1;
    Paddle m_paddle2;
    Ball m_ball;
    int m_score1;
    int m_score2;
    bool m_running;
};

#endif // GAME_H
