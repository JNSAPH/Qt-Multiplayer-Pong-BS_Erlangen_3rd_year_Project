#ifndef GAME_H
#define GAME_H

#include "Paddle.h"
#include "Ball.h"

#include <QObject>

#include <QJsonObject>
#include <QJsonDocument>
#include <QTimer>

#include "../socket/websocketserver.h"
#include "../utils/mariadb.h"
#include "../utils/logs.h"


class Game : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Get the singleton instance of the Game class
     * @return The Game instance
     */
    static Game& getInstance();

    /**
     * @brief Update the game state
     */
    void update();

    /**
     * @brief Start the game
     */
    void start();

    /**
     * @brief Stop the game
     * @note This method also Stops the game, Saves Logs to a CSV / Uploads them to a Database and resets the scores for m_score1 and m_score 2 to 0
     */
    void stop();

    /**
     * @brief Reset the game
     */
    void reset();

    /**
     * @brief Send the current state of the game
     */
    void sendState();

    /**
     * @brief Move the left paddle up
     */
    void movePaddle1Up();

    /**
     * @brief Move the left paddle down
     */
    void movePaddle1Down();

    /**
     * @brief Move the right paddle up
     */
    void movePaddle2Up();

    /**
     * @brief Move the right paddle down
     */
    void movePaddle2Down();

    /**
     * @brief Get the score of a player
     * @param player The player (1 or 2)
     * @return The player's score
     */
    int getScore(int player);

    /**
     * @brief Set the score of a player
     * @param player The player (1 or 2)
     * @param score The player's new score
     */
    void setScore(int player, int score);


private:
    /**
    * @var m_paddleLeftX
    * @brief The x-coordinate of the left paddle
    */
    int m_paddleLeftX = 29; // 29

    /**
     * @var m_paddleY
     * @brief The y-coordinate of the paddles
     */
    int m_paddleY = 230; //230

    /**
     * @var m_paddleRightX
     * @brief The x-coordinate of the right paddle
     */
    int m_paddleRightX = 625;

    /**
     * @var m_winningScore
     * @brief The score required to win the game
     */
    int m_winningScore = 5;


private:
    /**
     * @brief Constructor for the Game class (private to enforce singleton)
     */
    Game();

    /**
     * @brief Copy constructor (deleted to prevent copying)
     */
    Game(Game const&) = delete;

    /**
     * @brief Assignment operator (deleted to prevent assignment)
     */
    void operator=(Game const&) = delete;

    /**
     * @var m_score1
     * @brief The score of player 1
     */
    int m_score1;

    /**
     * @var m_score2
     * @brief The score of player 2
     */
    int m_score2;

    /**
     * @var m_running
     * @brief A flag indicating if the game is running
     */
    bool m_running;

    /**
     * @var m_timer
     * @brief A timer used to update the game
     */
    QTimer *m_timer;

    /**
     * @var m_playingFieldWidth
     * @brief The width of the playing field
     */
    int m_playingFieldWidth;

    /**
     * @var m_playingFieldHeight
     * @brief The height of the playing field
     */
    int m_playingFieldHeight;

    /**
     * @var m_paddle1
     * @brief The left paddle
     */
    Paddle m_paddle1;

    /**
     * @var m_paddle2
     * @brief The right paddle
     */
    Paddle m_paddle2;

    /**
     * @var m_ball
     * @brief The ball
     */
    Ball m_ball;

    /**
     * @var m_winnerBroadcast
     * @brief The message to be broadcasted when the game ends
     */
    QJsonObject m_winnerBroadcast;

    /**
     * @var logs
     * @brief A pointer to the LogUtils class to handle logging
     */
    LogUtils *logs;

    /**
     * @var db
     * @brief A pointer to the MariaDB class to handle database operations
     */
    MariaDB *db;


};

#endif // GAME_H
