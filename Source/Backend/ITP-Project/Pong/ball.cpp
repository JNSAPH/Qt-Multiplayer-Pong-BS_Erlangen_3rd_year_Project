#include "ball.h"
#include "paddle.h"
#include "qdebug.h"

Ball::Ball(qreal x, qreal y, qreal radius)
    : m_x(x), m_y(y), m_diameter(radius), m_xVelocity(0), m_yVelocity(0)
{
   setVelocity(m_xVelocity,m_yVelocity);
}

QPointF Ball::getPosition()
{
    return QPointF(m_x, m_y);
}

void Ball::setVelocity(qreal xVelocity, qreal yVelocity)
{
    m_xVelocity = xVelocity;
    m_yVelocity = yVelocity;
    while (m_xVelocity == 0)
    {
        m_xVelocity = ((double)QRandomGenerator::global()->generate() / QRandomGenerator::max()) * 3 - 1.5;
        m_xVelocity = m_xVelocity < 0 ? -ceil(abs(m_xVelocity) * 10) / 10 : ceil(m_xVelocity * 10) / 10;
        if (m_xVelocity == -0)
            m_xVelocity = 0;
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

void Ball::checkCollision(Paddle *paddle)
{
    // Get the paddle's position and size
    QPointF paddlePos = paddle->getPosition();
    int paddleWidth = paddle->getWidth();       //6
    int paddleHeight = paddle->getHeight();
    float ballMidX = m_x + m_diameter/2;
    float ballMidY = m_y + m_diameter/2;

    // Check if the ball collides with the paddle


    //Calculate Delta to nearest Side of Paddle
    float deltaX= (ballMidX - paddlePos.x());
    deltaX = deltaX > 0 ? (deltaX-paddleWidth) : abs(deltaX);

    //Is Ball in the correct X-Area
    if (deltaX > m_diameter/2) return;

    float deltaY= (ballMidY - (paddlePos.y()+paddleHeight/2));
    //Is Ball in the corret Y-Area

    if( abs(deltaY) >= paddleHeight/2 + m_diameter/2 ) return;

    //Paddle Face Hit

    if( abs(deltaY) < paddleHeight/2 - paddleHeight/20){
        m_xVelocity = -(m_xVelocity * 1.10);
        m_yVelocity *= 0.95;
         return;
    }

    if(deltaX <= m_diameter/6)
    {
        //HitOnBotDetected
        if(deltaY > 0 )
        {
            m_xVelocity *= (abs(m_xVelocity) <= 0.001)? -0.003/abs(m_xVelocity) : -1.1;
            m_yVelocity = (abs(m_yVelocity) <= 0.001)? (m_yVelocity  + 0.4) * 1.6 :  m_yVelocity * 1.6;
            return;
        }
        //HitOnTopDetected
        if(deltaY < 0 )
        {
            m_xVelocity *= (abs(m_xVelocity) <= 0.001)? -0.003/abs(m_xVelocity) : -1.1;
            m_yVelocity = (abs(m_yVelocity) <= 0.001)? (m_yVelocity  - 0.4 )* 1.6 :  m_yVelocity * 1.6;
            return;
        }
    }


    //HitOnBotDetected
    if(deltaY > m_diameter/6 )
    {
        m_xVelocity *= (abs(m_xVelocity) <= 0.001)? -0.003/abs(m_xVelocity) : -0.95;
        m_yVelocity = (abs(m_yVelocity)<= 0.001)? (m_yVelocity  + 0.4) * 1.4 :  m_yVelocity * 1.4;
        return;
    }
    //HitOnTopDetected
    if(deltaY < -m_diameter/6 )
    {
        m_xVelocity *= (abs(m_xVelocity) <= 0.001)? -0.003/abs(m_xVelocity) : -0.95;
        m_yVelocity = (abs(m_yVelocity)<= 0.001)? (m_yVelocity  - 0.4 )* 1.4 :  m_yVelocity * 1.4;

        return;
    }
    else
    {
        m_xVelocity *= -2 ;
        m_yVelocity *= -2 ;
        return;
    }
}


int Ball::getDiameter()
{
    return m_diameter;
}
