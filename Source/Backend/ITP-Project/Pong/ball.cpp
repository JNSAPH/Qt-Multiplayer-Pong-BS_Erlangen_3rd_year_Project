#include "Ball.h"
#include "Paddle.h"

Ball::Ball(qreal x, qreal y, qreal radius)
    : m_x(x), m_y(y), m_radius(radius), m_xVelocity(0), m_yVelocity(0)
{
}

QPointF Ball::getPosition()
{
    return QPointF(m_x, m_y);
}

void Ball::setVelocity(qreal xVelocity, qreal yVelocity)
{
    m_xVelocity = xVelocity;
    m_yVelocity = yVelocity;
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

void Ball::checkCollision(Paddle *paddle)
{
    // Check if the ball has collided with the paddle
    if (m_x + m_radius > paddle->getPosition().x() &&
        m_x - m_radius < paddle->getPosition().x() + paddle->getWidth() &&
        m_y + m_radius > paddle->getPosition().y() &&
        m_y - m_radius < paddle->getPosition().y() + paddle->getHeight())
    {
        // Reverse the x-velocity of the ball
        m_xVelocity = -m_xVelocity;
    }
}
