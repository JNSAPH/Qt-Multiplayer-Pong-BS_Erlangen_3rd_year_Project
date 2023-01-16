#include "Game.h"

Game& Game::getInstance() {
    static Game instance;
    return instance;
}


Game::Game()
    : m_score1(0),
      m_score2(0),
      m_playingFieldWidth(680),
      m_playingFieldHeight(540),
      m_paddle1(m_paddleLeftX, m_paddleY, 1, 80),
      m_paddle2(m_paddleRightX, m_paddleY, 1, 80),
      m_ball(-10, -10, 19)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(3); // (333 TPS)
    connect(m_timer, &QTimer::timeout, this, &Game::update);

    // set m_ball position to center of the playing field with radius of ball as offset
    m_ball.setPosition(m_playingFieldWidth / 2 - (m_ball.getRadius() / 2), m_playingFieldHeight / 2 - (m_ball.getRadius()) / 2);

    m_winnerBroadcast["code"] = 999;
}


/*
 * @Todo Score isn't updating because of the reset!!
 *
 */
void Game::update()
{
    if (m_ball.getPosition().x() < 0) {
        m_score2++;
        qDebug() << "Player 2 scored. Score: " << m_score2;
        // reset game
        this->reset();
    }

    // If ball hits wall on the right, increase score of player 1
    if (m_ball.getPosition().x() > m_playingFieldWidth) {
        m_score1++;
        qDebug() << "Player 1 scored. Score: " << m_score1;
        this->reset();
    }

    // If one Player reaches 5 points, stop the game and broadcast the winner
    if (m_score1 == 1) {
        qDebug() << "Player 1 won!";
        m_winnerBroadcast["winner"] = "1";
    } else if (m_score2 == 1) {
        qDebug() << "Player 2 won!";
        m_winnerBroadcast["winner"] = "2";
    }

    if (m_score1 == 1 || m_score2 == 1) {
        QJsonDocument doc(m_winnerBroadcast);
        QByteArray jsonData = doc.toJson();
        WebSocketServer::getInstance().broadcast(jsonData);
        
        this->stop();
        return;
    }

    // Check if ball is out of bounds
    if (m_ball.getPosition().y() <= 0 || m_ball.getPosition().y() >= m_playingFieldHeight) {
        m_ball.setVelocity(m_ball.getVelocity().x(), -m_ball.getVelocity().y());
    }

    m_ball.checkCollision(&m_paddle1);
    m_ball.checkCollision(&m_paddle2);
    m_ball.updatePosition();
    this->sendState();
}

void Game::start()
{
    // Start the game
    m_timer->start();
}

void Game::stop()
{
    // Stop the game
    m_timer->stop();
    m_score1 = 0;
    m_score2 = 0;
}

void Game::reset()
{
    // Reset the game
    // you can reset the paddles and ball position, and scores
    m_paddle1.setPosition(m_paddleLeftX, m_paddleY);
    m_paddle2.setPosition(m_paddleRightX, m_paddleY);
    m_ball.setPosition(m_playingFieldWidth / 2 - (m_ball.getRadius() / 2), m_playingFieldHeight / 2 - (m_ball.getRadius()) / 2);
    m_ball.setVelocity(0, 0);
}

void Game::sendState()
{
    // Serialize the state of the game to json
    QJsonObject json;
    json["code"] = 204;
    json["paddle1"] = QJsonObject({
                            {"x", m_paddle1.getPosition().x()},
                            {"y", m_paddle1.getPosition().y()}
                        });
    json["paddle2"] = QJsonObject({
                            {"x", m_paddle2.getPosition().x()},
                            {"y", m_paddle2.getPosition().y()}
                        });
    json["ball"] = QJsonObject({
                            {"x", m_ball.getPosition().x()},
                            {"y", m_ball.getPosition().y()},
                            {"vx", m_ball.getVelocity().x()},
                            {"vy", m_ball.getVelocity().y()}
                        });
    json["score1"] = m_score1;
    json["score2"] = m_score2;
    json["running"] = m_running;

    // Send the json object to all connected clients
    QJsonDocument doc(json);
    QByteArray jsonData = doc.toJson();

    // Broadcast jsonData
    WebSocketServer::getInstance().broadcast(jsonData);
}


int Game::getScore(int player)
{
    if (player == 1)
        return m_score1;
    if (player == 2)
        return m_score2;
    return -1;
}

void Game::movePaddle1Up() {
    m_paddle1.moveUp();
}
void Game::movePaddle1Down() {
    m_paddle1.moveDown();
}
void Game::movePaddle2Up() {
    m_paddle2.moveUp();
}
void Game::movePaddle2Down() {
    m_paddle2.moveDown();
}

void Game::setScore(int player, int score)
{
    if (player == 1)
        m_score1 = score;
    if (player == 2)
        m_score2 = score;
}
