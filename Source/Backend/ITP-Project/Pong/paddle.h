#ifndef PADDLE_H
#define PADDLE_H

#include "QtCore/qstring.h"
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
    Paddle(qreal x, qreal y, qreal width, qreal height, QString playerId);

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

    /**
     * @brief returns m_FaceHit X/Y 
     * @param x decides if return is x or y
    */
    double getFace(bool X);
    
    /**
     * @brief returns m_SideHit X/Y 
     * @param x decides if return is x or y
    */
    double getSide(bool X);
    
    /**
     * @brief returns m_EdgeHit X/Y 
     * @param x decides if return is x or y
    */
    double getEdge(bool X);

    /**
     * @brief sets m_FaceHit X/Y 
     * @param x decides if set is x or y
     * @param value is the value
    */
    void setFace(bool X, double value);
    
    /**
     * @brief sets m_SideHit X/Y 
     * @param x decides if set is x or y
     * @param value is the value
    */
    void setSide(bool X, double value);
    
    /**
     * @brief sets m_EdgeHit X/Y 
     * @param x decides if set is x or y
     * @param value is the value
    */
    void setEdge(bool X, double value);

    /**
     * @brief Sets PlayerID
     * @param p_playerId is the Id of the Player
     */
    void setId(QString p_playerId);

    /**
     * @brief addScore
     * @param score
     */
    void addScore(int score);

    /**
     * @brief getScore
     * @return
     */
    int getScore();

    /**
     * @brief getId
     * @returns the Id of the Player Playing the paddle
     */
    QString getId();

private:
    /**
     * @brief The x-coordinate of the paddle
    */
    qreal m_x;

    /**
     * @brief ID of the Player playing this paddle
     */
    QString m_playerId;

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

    /**
     * @var m_FaceHitX
     * @brief Intensity of Rebound in X Direction if Hit on Face
    */
    double m_FaceHitX;
    
    /**
     * @var m_FaceHitY
     * @brief Intensity of Rebound in Y Direction if Hit on Face
    */
    double m_FaceHitY;
    
    /**
     * @var m_EdgeHitX
     * @brief Intensity of Rebound in X Direction if Hit on Edge
    */
    double m_EdgeHitX;
    
    /**
     * @var m_EdgeHitY
     * @brief Intensity of Rebound in Y Direction if Hit on Edge
    */
    double m_EdgeHitY;
    
    /**
     * @var m_SideHitX
     * @brief Intensity of Rebound in X Direction if Hit on Side
    */
    double m_SideHitX;
    
    /**
     * @var m_SideHitY
     * @brief Intensity of Rebound in Y Direction if Hit on Side
    */
    double m_SideHitY;

    /**
     * @brief m_Score
     */
    int m_Score;

};

#endif // PADDLE_H
