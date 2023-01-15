#ifndef BALL_H
#define BALL_H

#include <QPointF>

class Paddle;

class Ball
{
public:
    Ball(qreal x, qreal y, qreal radius);

    QPointF getPosition();
    void setVelocity(qreal xVelocity, qreal yVelocity);
    QPointF getVelocity();
    void updatePosition();
    void checkCollision(Paddle* paddle);

private:
    qreal m_x;
    qreal m_y;
    qreal m_radius;
    qreal m_xVelocity;
    qreal m_yVelocity;
};

#endif // BALL_H
