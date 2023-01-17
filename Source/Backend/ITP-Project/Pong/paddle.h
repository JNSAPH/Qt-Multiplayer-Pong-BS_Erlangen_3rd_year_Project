#ifndef PADDLE_H
#define PADDLE_H

#include <QPointF>

/**
 * @class Paddle
 * @brief The Paddle class represents a paddle in the game of Pong
 *
 * This class provides methods for moving the paddle and getting and setting its position and size.
 */
class Paddle
{
public:
    /**
     * @brief Construct a new Paddle object
     * @param x The x-coordinate of the paddle
     * @param y The y-coordinate of the paddle
     * @param width The width of the paddle
     * @param height The height of the paddle
     */
    Paddle(qreal x, qreal y, qreal width, qreal height);

    /**
     * @brief Move the paddle up
     */
    void moveUp();

    /**
     * @brief Move the paddle down
     */
    void moveDown();

    /**
     * @brief Set the direction the paddle is moving
     * @param direction The direction the paddle is moving (up or down)
     */
    void setDirection(int direction);

    /**
     * @brief Get the width of the paddle
     * @return The width of the paddle as an int
     */
    int getWidth();

    /**
     * @brief Get the height of the paddle
     * @return The height of the paddle as an int
     */
    int getHeight();

    /**
     * @brief Set the position of the paddle
     * @param x The x-coordinate of the paddle
     * @param y The y-coordinate of the paddle
     */
    void setPosition(int x, int y);
    
    /**
     * @brief Get the position of the paddle
     * @return The position of the paddle as a QPointF
    */
    QPointF getPosition();

private:
    /**
     * @brief The x-coordinate of the paddle
    */
    qreal m_x;

    /**
     * @brief The y-coordinate of the paddle
    */
    qreal m_y;
    
    /**
     * @brief The width of the paddle
    */
    qreal m_width;

    /**
     * @brief The height of the paddle
    */
    qreal m_height;

    /**
     * @brief The direction the paddle is moving
     * @important Not yet implemented
    */
    int m_direction;
};

#endif // PADDLE_H
