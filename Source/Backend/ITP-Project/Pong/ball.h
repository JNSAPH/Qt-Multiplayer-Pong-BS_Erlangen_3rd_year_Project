#ifndef BALL_H
#define BALL_H

#include <QPointF>
#include <QRandomGenerator>

#include <cmath>

/**
 * @brief Forwad Declaration for Paddle
 */
class Paddle;

/**
 * @class Ball
 * @brief The Ball class represents a ball in the game
 *
 * This class provides methods for getting and setting the position, velocity, and radius of the ball,
 * and for updating the position of the ball based on its velocity. It also provides a method for checking
 * collision with a Paddle object.
 */
class Ball
{
public:
    /**
     * @brief Constructor for the Ball class
     * @param x The initial x-coordinate of the ball
     * @param y The initial y-coordinate of the ball
     * @param radius The radius of the ball
     */
    Ball(qreal x, qreal y, qreal radius);

    /**
     * @brief Get the current position of the ball
     * @return The position of the ball as a QPointF
     */
    QPointF getPosition();

    /**
     * @brief Set the velocity of the ball
     * @param xVelocity The x-velocity of the ball
     * @param yVelocity The y-velocity of the ball
     */
    void setVelocity(qreal xVelocity, qreal yVelocity);

    /**
     * @brief Get the velocity of the ball
     * @return The velocity of the ball as a QPointF
     */
    QPointF getVelocity();

    /**
     * @brief Update the position of the ball based on its velocity
     */
    void updatePosition();

    /**
     * @brief set the position of the ball
     * @param x the x coordinate of the ball
     * @param y the y coordinate of the ball
     */
    void setPosition(int x, int y);
    /**
     * @brief Check for collision between the ball and a Paddle object
     * @param paddle A pointer to the Paddle object to check for collision with
     */
    void checkCollision(Paddle* paddle);

    /**
     * @brief Get the radius of the ball
     * @returns The radius of the ball as an int
     */
    int getRadius();

private:
    /**
    * @var m_x
    * @brief The x-coordinate of the ball
    */
    qreal m_x;

    /**
    * @var m_y
    * @brief The y-coordinate of the ball
    */
    qreal m_y;

    /**
    * @var m_radius
    * @brief The radius of the ball
    */
    qreal m_radius;

    /**
    * @var m_xVelocity
    * @brief The x-velocity of the ball
    */
    qreal m_xVelocity;

    /**
    * @var m_yVelocity
    * @brief The y-velocity of the ball
    */
    qreal m_yVelocity;
    };


#endif // BALL_H
