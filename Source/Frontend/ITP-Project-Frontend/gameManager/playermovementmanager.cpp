#include "playermovementmanager.h"

playerMovementManager::playerMovementManager(QObject *parent) : QObject(parent){ }


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
        // call view to change to game
        break;
    default:
        qDebug() << jsonObject["message"].toString();
        break;
    }
}
