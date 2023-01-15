#include "Ball.h"
#include "Paddle.h"
#include "qdebug.h"


Ball::Ball(qreal x, qreal y, qreal radius)
    : m_x(x), m_y(y), m_radius(radius), m_xVelocity(0), m_yVelocity(0)
{
    while(m_xVelocity == 0 || m_xVelocity < 0.2)
    {
        m_xVelocity = ((double)QRandomGenerator::global()->generate()/QRandomGenerator::max())*3 - 1.5;
        m_xVelocity = m_xVelocity < 0 ? -ceil(abs(m_xVelocity) * 10) / 10 : ceil(m_xVelocity * 10) / 10;
        if (m_xVelocity == -0) m_xVelocity = 0;
    }
    
}

QPointF Ball::getPosition()
{
    return QPointF(m_x, m_y);
}

void Ball::setVelocity(qreal xVelocity, qreal yVelocity)
{

    m_xVelocity = xVelocity;
    m_yVelocity = yVelocity;

    while(m_xVelocity == 0)
    {
        m_xVelocity = ((double)QRandomGenerator::global()->generate()/QRandomGenerator::max())*3 - 1.5;
        m_xVelocity = m_xVelocity < 0 ? -ceil(abs(m_xVelocity) * 10) / 10 : ceil(m_xVelocity * 10) / 10;
        if (m_xVelocity == -0) m_xVelocity = 0;
    }


}

QPointF Ball::getVelocity()
{
    return QPointF(m_xVelocity, m_yVelocity);
}

void Ball::updatePosition()
{
    // Update the position of the ball based on its velocity 
    m_x += m_xVelocity;
    m_y += m_yVelocity;
}

void Ball::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}


void Ball::checkCollision(Paddle* paddle) {
    // Get the paddle's position and size
    QPointF paddlePos = paddle->getPosition();
    int paddleWidth = paddle->getWidth();
    int paddleHeight = paddle->getHeight();

    // Check if the ball collides with the paddle
    if (m_x + m_radius > paddlePos.x() &&
        m_x - m_radius < paddlePos.x() + paddleWidth &&
        m_y + m_radius > paddlePos.y() &&
        m_y - m_radius < paddlePos.y() + paddleHeight) {
        // Reverse the x velocity of the ball to make it bounce back
        m_xVelocity = -m_xVelocity;
    }
}

/*
 *
    // Check if the ball is colliding with the paddle
    if (m_x + m_radius >= paddle->getPosition().x() &&
        m_x - m_radius <= paddle->getPosition().x() + paddle->getWidth())
    {
        qDebug() << "Coll 1";
    }
*/



int Ball::getRadius()
{
    return m_radius;
}
