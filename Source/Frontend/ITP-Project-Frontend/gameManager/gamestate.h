#ifndef GAMESTATE_H
#define GAMESTATE_H

struct Ball {
    double vx;
    double vy;
    double x;
    double y;
    double diameter;
};

struct Paddle {
    double x;
    double y;
    double width;
    double height;
};

class GameState
{
public:
    static GameState& getInstance() {
        static GameState instance;
        return instance;
    }

    GameState(GameState const&) = delete;
    GameState(GameState&&) = delete;
    GameState& operator=(GameState const&) = delete;
    GameState& operator=(GameState &&) = delete;

    Ball getBall() const;
    Paddle getPaddle1() const;
    Paddle getPaddle2() const;
    int getScore1() const;
    int getScore2() const;
    bool isRunning() const;
    void setBall(double vx, double vy, double x, double y, double diameter);
    void setPaddle1(double x, double y, double width, double height);
    void setPaddle2(double x, double y, double width, double height);
    void setScore1(int score);
    void setScore2(int score);
    void setRunning(bool running);


private:
    GameState();
    Ball m_ball;
    Paddle m_paddle1;
    Paddle m_paddle2;
    int score1;
    int score2;
    bool m_running;
};

#endif // GAMESTATE_H
