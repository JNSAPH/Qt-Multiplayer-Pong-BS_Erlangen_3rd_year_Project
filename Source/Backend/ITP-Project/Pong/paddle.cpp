#include "Paddle.h"

Paddle::Paddle(qreal x, qreal y, qreal width, qreal height)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_direction(0)
{
}

void Paddle::moveUp()
{
    m_direction = -1;
}

void Paddle::moveDown()
{
    m_direction = 1;
}

void Paddle::setDirection(int direction)
{
    m_direction = direction;
}

QPointF Paddle::getPosition()
{
    return QPointF(m_x, m_y);
}
