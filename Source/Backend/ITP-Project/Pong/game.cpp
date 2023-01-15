#include "Game.h"

Game& Game::getInstance() {
    static Game instance;
    return instance;
}

Game::Game()
    : m_paddle1(0, 200, 6, 80),
      m_paddle2(642-6, 200, 6, 80),
      m_ball(320, 240, 19),
      m_score1(0),
      m_score2(0)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(250);
    connect(m_timer, &QTimer::timeout, this, &Game::update);
}


void Game::update()
{
    // Update the positions of the paddles and ball based on the inputs received from the clients
    // you can use the updatePosition() method of the Paddle and Ball classes,
    // and the checkCollision() method of the Ball class
    // to update the positions of the paddles and ball
    // also you can check if the ball hit the wall and update the score accordingly
    qDebug() << "Updating";
}

void Game::start()
{
    // Start the game
    qDebug() << "RAN THE START METHOD!!";
    m_timer->start();
    m_running = true;
}

void Game::stop()
{
    // Stop the game
    m_timer->stop();
    //m_running = false;
}

void Game::reset()
{
    // Reset the game
    // you can reset the paddles and ball position, and scores
    m_paddle1.setPosition(0, 0);
    m_paddle2.setPosition(0, 0);
    m_ball.setPosition(0, 0);
    m_score1 = 0;
    m_score2 = 0;
}

void Game::sendState()
{
    // Serialize the state of the game to json
    QJsonObject json;
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
