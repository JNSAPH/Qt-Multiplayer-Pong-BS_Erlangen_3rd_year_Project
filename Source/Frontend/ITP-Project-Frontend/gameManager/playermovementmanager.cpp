#include "playermovementmanager.h"

#include "../Views/view_waitinginqueue.h"


playerMovementManager::playerMovementManager(QObject *parent) : QObject(parent){
}


void playerMovementManager::onTextMessageReceived(const QString &message)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject jsonObject = jsonDoc.object();

    switch (jsonObject["code"].toInt()) {
    case 200:
        // Player Joined
        qDebug() << "Player " << jsonObject["PlayerNumber"].toInt() << " Joined";
        break;
    case 201:
        // Game is starting
        qDebug() << "Game is starting";

        view_waitingInQueue::startGame();
        break;
        // Open Multiplayer View
        break;
    case 203:
        qDebug() << "Player " << jsonObject["PlayerNumber"].toInt() << " disconnected.";
    default:
        qDebug() << jsonObject["message"].toString();
        break;
    }
}
