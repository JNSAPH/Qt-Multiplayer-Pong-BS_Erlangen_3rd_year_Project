#include "ball.h"
#include "paddle.h"
#include "qdatetime.h"
#include "qdebug.h"

Ball::Ball(qreal x, qreal y, qreal radius)
    : m_x(x), m_y(y), m_diameter(radius), m_xVelocity(0), m_yVelocity(0)
{
    m_minRndVelX = 800;
    m_maxRndVelX = 1100;
    m_minRndVelY = 250;
    m_maxRndVelY = 500;

   setRandomVelocity();
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

void Ball::setRandomVelocity()
{
    double rndXVel;
    double rndYVel;

    // Generate random velocity between m_minRndVelY and m_maxRndVelY for y
    // Generate random velocity between m_minRndVelX and m_maxRndVelX for x

    rndXVel = ((double)QRandomGenerator::global() -> bounded(m_minRndVelX,m_maxRndVelX) / 1000);
    rndYVel = ((double)QRandomGenerator::global() -> bounded(m_minRndVelY,m_maxRndVelY) / 1000);


    // Set the velocity to be either positive or negative
    m_yVelocity = (QRandomGenerator::global()->generate() % 2 )== 0 ? rndYVel : -rndYVel;
    m_xVelocity = (QRandomGenerator::global()->generate() % 2 )== 0 ? rndXVel : -rndXVel;

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


void Ball::checkOutOfBounds(int maxHeight)
{
    // Check if ball is out of bounds
    if (m_y <= 0 || m_y  >= maxHeight + m_diameter) { m_yVelocity = -m_yVelocity;}
}

void Ball::checkCollision(Paddle *paddle)
{
    // Get the paddle's position and size
    QPointF paddlePos = paddle->getPosition();
    int paddleWidth = paddle->getWidth();       //6
    int paddleHeight = paddle->getHeight();
    float ballMidX = m_x + m_diameter/2;
    float ballMidY = m_y + m_diameter/2;

    //Calculate Delta to nearest Side of Paddle
    float deltaX= (ballMidX - paddlePos.x());
    deltaX = deltaX > 0 ? (deltaX-paddleWidth) : abs(deltaX);

    //Is Ball in the correct X-Area
    if (deltaX > m_diameter/2) return;

    float deltaY= (ballMidY - (paddlePos.y()+paddleHeight/2));

    //Is Ball in the corret Y-Area
    if( abs(deltaY) >= paddleHeight/2 + m_diameter/2 ) return;

    // Ball Hit Paddle Zone
    qDebug() << paddle->getId();
    Score::addScore(paddle->getId(), 50);

    //Paddle Face Hit / Ball Front
    if( abs(deltaY) < paddleHeight/2 - paddleHeight/20){
        m_xVelocity = -(m_xVelocity * paddle -> getFace(true));
        m_yVelocity *= paddle -> getFace(false);
         return;
    }

    //Paddle Edge Hit / Ball Top-Bot
    if(deltaX <= m_diameter/6)
    {
        //HitOnBotDetected
        if(deltaY > 0 )
        {
            m_xVelocity *= (abs(m_xVelocity) <= 0.001)? -0.003/abs(m_xVelocity) : -paddle -> getEdge(true);
            m_yVelocity = (abs(m_yVelocity) <= 0.001)? (m_yVelocity  + 0.4) * paddle -> getEdge(false) :  m_yVelocity * paddle -> getEdge(false);

            qDebug() << paddle->getId();
            Score::addScore(paddle->getId(), 100);

            return;
        }
        //HitOnTopDetected
        if(deltaY < 0 )
        {
            m_xVelocity *= (abs(m_xVelocity) <= 0.001)? -0.003/abs(m_xVelocity) : -paddle -> getEdge(true);
            m_yVelocity = (abs(m_yVelocity) <= 0.001)? (m_yVelocity  - 0.4 )* paddle -> getEdge(false) :  m_yVelocity * paddle -> getEdge(false);

            qDebug() << paddle->getId();
            Score::addScore(paddle->getId(), 100);

            return;
        }
    }

    //Paddle Side Hit / Ball Corner

    //HitOnBotDetected
    if(deltaY > m_diameter/6 )
    {
        m_xVelocity *= (abs(m_xVelocity) <= 0.001)? -0.003/abs(m_xVelocity) : -paddle -> getSide(true);
        m_yVelocity = (abs(m_yVelocity)<= 0.001)? (m_yVelocity  + 0.4) * paddle -> getSide(false) :  m_yVelocity * paddle -> getSide(false);
       
        qDebug() << paddle->getId();
        Score::addScore(paddle->getId(), 75);
       
        return;
    }
    //HitOnTopDetected
    if(deltaY < -m_diameter/6 )
    {
        m_xVelocity *= (abs(m_xVelocity) <= 0.001)? -0.003/abs(m_xVelocity) : -paddle -> getSide(true);
        m_yVelocity = (abs(m_yVelocity)<= 0.001)? (m_yVelocity  - 0.4 )* paddle -> getSide(false) :  m_yVelocity * paddle -> getSide(false);
       
        qDebug() << paddle->getId();
        Score::addScore(paddle->getId(), 75);
       
        return;
    }
    else    //Ball Center Hit
    {
        m_xVelocity *= - 2 * paddle -> getFace(true)  ;
        m_yVelocity *= - 2 * paddle -> getFace(false) ;
       
        /*
        Hier keinen score adden, weil das der funny glitch part ist :) oder 10 per hit?
        */
       
        return;
    }
}

int Ball::getDiameter()
{
    return m_diameter;
}
