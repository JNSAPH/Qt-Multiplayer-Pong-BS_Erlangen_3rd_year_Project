#include "queuemanager.h"

#include <QDebug>

QQueue<int> QueueManager::queue;
QMap<QUuid,QQueue<int>> QueueManager::games;
QUuid QueueManager::gameId;


const char* QueueFullException::what() const throw() {
    return "Queue is full";
}

QueueManager::QueueManager(){ }

void QueueManager::addPlayer(int playerId)
{
    if(queue.size()<2)
    {
        queue.enqueue(playerId);
        qDebug() << "Added Player " << playerId << " to Queue";
    }
    else
    {
        // handle case when the queue is full
        throw QueueFullException();
        return;
    }

    if(queue.size() == 2)
    {
        gameId = QUuid::createUuid();
        games[gameId] = queue;
        qDebug() << "Creating UUID: " << gameId;
    }
}

int QueueManager::removePlayer(int playerId)
{
    if (!queue.isEmpty())
    {
        int index = queue.indexOf(playerId);
        if(index != -1)
        {
            queue.removeAt(index);
            return playerId;
        }
        else
        {
            // handle case when the player is not in the queue
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

int QueueManager::getQueueSize()
{
    return queue.size();
}

QUuid QueueManager::getGameId()
{
    return gameId;
}

// don't know if we need this, just in case tho
bool QueueManager::joinGame(QUuid gameId, int playerId)
{
    if(games.contains(gameId))
    {
        games[gameId].enqueue(playerId);
        return true;
    }
    return false;
}
