#include "playermanager.h"

PlayerManager::PlayerManager()
{

}

void PlayerManager::setPlayerNumber(int p_PlayerNumber) {
    m_PlayerNumber = p_PlayerNumber;
}

int PlayerManager::getPlayerNumber() {
    return m_PlayerNumber;
}

int PlayerManager::getScore() {
    return m_score;
}

void PlayerManager::setScore(int score) {
    m_score = score;
}

void PlayerManager::setUUID(QString p_UUID) {
    m_UUID = p_UUID;
}

QString PlayerManager::getUUID() {
    return m_UUID;
}
