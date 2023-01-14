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
    static void addPlayer(QString playerId);
    static int removePlayer(QString playerId);
    static int getQueueSize();
    static QUuid getGameId();
    static bool joinGame(QUuid gameId, QString playerId);

private:
    static QQueue<QString> queue;
    static QMap<QUuid,QQueue<QString>> games;
    static QUuid gameId;
};

#endif // QUEUEMANAGER_H
