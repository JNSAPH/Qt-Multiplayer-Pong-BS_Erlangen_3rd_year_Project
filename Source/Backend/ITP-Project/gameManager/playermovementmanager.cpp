#include "playermovementmanager.h"

playerMovementManager::playerMovementManager(QObject *parent) : QObject(parent){ }

void playerMovementManager::onTextMessageReceived(const QString &message)
{
    // Implementation
    qDebug() << message;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject jsonObject = jsonDoc.object();

    qDebug() << jsonObject["player"].toString();
    qDebug() << jsonObject["action"].toString();

    // If Player 1:

    // If Player 2:
}
