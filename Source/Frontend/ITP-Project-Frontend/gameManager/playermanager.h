#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <QObject>

class PlayerManager
{
public:
    static PlayerManager& getInstance() {
        static PlayerManager instance;
        return instance;
    }
    // Delete copy and move constructors and assign operators
    PlayerManager(PlayerManager const&) = delete;             // Copy construct
    PlayerManager(PlayerManager&&) = delete;                  // Move construct
    PlayerManager& operator=(PlayerManager const&) = delete;  // Copy assign
    PlayerManager& operator=(PlayerManager &&) = delete;      // Move assign

    void setPlayerNumber(int p_PlayerNumber);
    int getPlayerNumber();

    int getScore();
    void setScore(int score);

    void setUUID(QString p_UUID);
    void setPoints(int score);
    QString getUUID();

private:
    PlayerManager();
    int m_PlayerNumber;
    QString m_UUID = "";
    int m_score;
};

#endif // PLAYERMANAGER_H
