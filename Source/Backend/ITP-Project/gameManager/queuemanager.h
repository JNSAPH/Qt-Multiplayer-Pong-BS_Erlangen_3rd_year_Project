#ifndef QUEUEMANAGER_H
#define QUEUEMANAGER_H

#include <QQueue>
#include <QUuid>
#include <QMap>

class QueueFullException : public std::exception {
public:
    const char* what() const throw();
};

class QueueManager
{
public:
    QueueManager();
    static void addPlayer(int playerId);
    static int removePlayer(int playerId);
    static int getQueueSize();
    static QUuid getGameId();
    static bool joinGame(QUuid gameId, int playerId);

private:
    static QQueue<int> queue;
    static QMap<QUuid,QQueue<int>> games;
    static QUuid gameId;
};

#endif // QUEUEMANAGER_H
