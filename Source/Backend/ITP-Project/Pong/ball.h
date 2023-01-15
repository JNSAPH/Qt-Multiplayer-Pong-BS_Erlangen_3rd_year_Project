#ifndef BALL_H
#define BALL_H

#include <QPointF>
#include <QRandomGenerator>

#include <cmath>

class Paddle;

class Ball
{
public:
    Ball(qreal x, qreal y, qreal radius);

    QPointF getPosition();
    void setVelocity(qreal xVelocity, qreal yVelocity);
    QPointF getVelocity();
    void updatePosition();
    void setPosition(int x, int y);
    void checkCollision(Paddle* paddle);
    int getRadius();

private:
    qreal m_x;
    qreal m_y;
    qreal m_radius;
    qreal m_xVelocity;
    qreal m_yVelocity;
};

#endif // BALL_H
