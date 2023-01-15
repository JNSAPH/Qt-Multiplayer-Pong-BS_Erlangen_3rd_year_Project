#include "Paddle.h"

#include <QDebug>

Paddle::Paddle(qreal x, qreal y, qreal width, qreal height)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_direction(0)
{
}

void Paddle::moveUp()
{
    if (m_y > 0)
        m_y = m_y - 10;
}

void Paddle::moveDown()
{
    if (m_y < (540 - m_height))
        m_y = m_y + 10;
}

void Paddle::setDirection(int direction)
{
    m_direction = direction;
}

QPointF Paddle::getPosition()
{
    return QPointF(m_x, m_y);
}

void Paddle::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}

int Paddle::getWidth()
{
    return m_width;
}

int Paddle::getHeight()
{
    return m_width;
}
