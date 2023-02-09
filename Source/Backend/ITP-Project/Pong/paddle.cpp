#include "paddle.h"

#include <QDebug>

Paddle::Paddle(qreal x, qreal y, qreal width, qreal height)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_direction(0)
    , m_FaceHitX(1.12), m_FaceHitY (0.95),  m_EdgeHitX(1.05), m_EdgeHitY(1.6), m_SideHitX(1.01), m_SideHitY(1.4)
{
}

void Paddle::moveUp()
{
    if (m_y > 0)
        m_y = m_y - 15;
}

void Paddle::moveDown()
{
    if (m_y < (540 - m_height))
        m_y = m_y + 20;
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
    return m_height;
}


double Paddle::getFace(bool x)
{
    if(x) return m_FaceHitX;
    return m_FaceHitY;
}

double Paddle::getSide(bool x)
{
    if(x) return m_SideHitX;
    return m_SideHitY;
}

double Paddle::getEdge(bool x)
{
    if(x) return m_EdgeHitX ;
    return m_EdgeHitY;
}


void Paddle::setFace(bool x, double value)
{
    if(x) m_FaceHitX = value;
    m_FaceHitY = value;
}
void Paddle::setSide(bool x, double value)
{
    if(x) m_SideHitX = value;
    m_SideHitY = value;
}
void Paddle::setEdge(bool x, double value)
{
    if(x) m_EdgeHitX = value;
    m_EdgeHitY = value;
}
    
   
