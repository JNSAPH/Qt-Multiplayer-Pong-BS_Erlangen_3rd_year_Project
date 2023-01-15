#ifndef PADDLE_H
#define PADDLE_H

#include <QPointF>

class Paddle
{
public:
    Paddle(qreal x, qreal y, qreal width, qreal height);

    void moveUp();
    void moveDown();
    void setDirection(int direction);
    QPointF getPosition();

private:
    qreal m_x;
    qreal m_y;
    qreal m_width;
    qreal m_height;
    int m_direction;
};

#endif // PADDLE_H
