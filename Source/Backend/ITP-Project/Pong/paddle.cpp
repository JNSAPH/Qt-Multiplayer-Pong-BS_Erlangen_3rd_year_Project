#include "paddle.h"

#include <QDebug>

Paddle::Paddle(qreal x, qreal y, qreal width, qreal height)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_direction(0)
    , m_FaceHitX(1.10), m_FaceHitY (0.95), m_EdgeHitX(1), m_EdgeHitY(1), m_SideHitX(1), m_SideHitY(1)
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
    return m_height;
}


int Paddle::getFace(bool X) => {x? return m_FaceHitX : return m_FaceHitY;} 

int Paddle::getSide(bool X) => {x? return m_SideHitX : return m_SideHitY;}     

int Paddle::getEdge(bool X) => {x? return m_EdgeHitX : return m_EdgeHitY;} 


int Paddle::setFace(bool X, int value) => {x? return m_FaceHitX = value; : return  m_FaceHitY = value;}
int Paddle::setSide(bool X, int value) => {x? return m_SideHitX = value; : return  m_SideHitY = value;} 
int Paddle::setEdge(bool X, int value) => {x? return m_EdgeHitX = value; : return  m_EdgeHitY = value;} 
    
   