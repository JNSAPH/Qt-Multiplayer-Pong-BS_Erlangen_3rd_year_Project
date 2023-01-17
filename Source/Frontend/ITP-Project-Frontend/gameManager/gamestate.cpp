#include "gamestate.h"

GameState::GameState()
{

}

Ball GameState::getBall() const
{
    return m_ball;
}

Paddle GameState::getPaddle1() const
{
    return m_paddle1;
}

Paddle GameState::getPaddle2() const
{
    return m_paddle2;
}

int GameState::getScore1() const
{
    return score1;
}

int GameState::getScore2() const
{
    return score2;
}

bool GameState::isRunning() const
{
    return m_running;
}

void GameState::setBall(double vx, double vy, double x, double y, double radius)
{
    m_ball.vx = vx;
    m_ball.vy = vy;
    m_ball.x = x;
    m_ball.y = y;
    m_ball.radius = radius;
}

void GameState::setPaddle1(double x, double y, double width, double height)
{
    m_paddle1.x = x;
    m_paddle1.y = y;
    m_paddle1.width = width;
    m_paddle1.height = height;
}

void GameState::setPaddle2(double x, double y, double width, double height)
{
    m_paddle2.x = x;
    m_paddle2.y = y;
    m_paddle2.width = width;
    m_paddle2.height = height;
}

void GameState::setScore1(int score)
{
    score1 = score;
}

void GameState::setScore2(int score)
{
    score2 = score;
}

void GameState::setRunning(bool running)
{
    m_running = running;
}


