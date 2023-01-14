#include "playercommunicationmanager.h"

#include "../Views/view_waitinginqueue.h"


playerCommunicationManager::playerCommunicationManager(QObject *parent) : QObject(parent){

}


void playerCommunicationManager::onTextMessageReceived(const QString &message)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject jsonObject = jsonDoc.object();

    qDebug() << "GOT MESSAGE";

    switch (jsonObject["code"].toInt()) {
    case 200:
        // Player Joined
        qDebug() << "Player " << jsonObject["PlayerNumber"].toInt() << " Joined";
        // Set Player_number to Received player number
        break;
    case 201:
        // Game is starting
        qDebug() << "Game is starting";
        view_waitingInQueue::getInstance()->startGame();
        break;
    case 203:
        // Player Disconnected
        qDebug() << jsonObject["message"].toString();
        qDebug() << "Player " << jsonObject["PlayerNumber"].toInt() << " disconnected.";
        break;
    default:
        qDebug() << jsonObject["message"].toString();
        break;
    }
}
