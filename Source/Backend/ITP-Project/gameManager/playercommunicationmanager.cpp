#include "playercommunicationmanager.h"

playerCommunicationManager::playerCommunicationManager(QObject *parent) : QObject(parent){ }

void playerCommunicationManager::onTextMessageReceived(const QString &message)
{
    // Implementation
    qDebug() << message;

}
