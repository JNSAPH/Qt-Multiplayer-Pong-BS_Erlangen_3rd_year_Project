#ifndef QUEUEMANAGER_H
#define QUEUEMANAGER_H

#include <QQueue>
#include <QUuid>
#include <QMap>

/**
 * @class QueueFullException
 * @brief Exception thrown when the queue is full
 *
 * This exception is thrown when a player tries to join a full queue.
 */
class QueueFullException : public std::exception {
public:
    /**
     * @brief Get the error message associated with the exception
     * @return The error message as a C-style string
     */
    const char* what() const throw();
};

/**
 * @class QueueManager
 * @brief The QueueManager class manages a queue of players
 *
 * This class provides methods for adding and removing players from a queue, as well as getting the size of the queue,
 * creating a new game, and resetting the queue.
 */
class QueueManager
{
public:
    /**
     * @brief Constructor for the QueueManager class
     */
    QueueManager();

    /**
     * @brief Add a player to the queue
     * @param playerId The ID of the player to add
     * @throws QueueFullException When the queue is already full
     */
    static void addPlayer(QString playerId);

    /**
     * @brief Remove a player from the queue
     * @param playerId The ID of the player to remove
     * @return 0 if successful, -1 if the player is not in the queue
     */
    static int removePlayer(QString playerId);

    /**
     * @brief Get all current members in Queue
     * @return All membersin Queue
     */
    static QQueue<QString> getQueueMembers();

    /**
     * @brief Get the current size of the queue
     * @return The size of the queue
     */
    static int getQueueSize();

    /**
     * @brief Get the current game's ID
     * @return The game's ID
     */
    static QUuid getGameId();

    /**
     * @brief Join a game
     * @param gameId The ID of the game to join
     * @param playerId The ID of the player joining the game
     * @return true if successful, false if the game does not exist
     */
    static bool joinGame(QUuid gameId, QString playerId);

    /**
     * @brief Reset the queue
     */
    static void resetQueue();

private:
    /**
     * @var queue
     * @brief The queue of players
     */
    static QQueue<QString> queue;

    /**
     * @var games
     * @brief The games that are being played
     */
    static QMap<QUuid,QQueue<QString>> games;

    /**
     * @var gameId
     * @brief The ID of the current game
     */
    static QUuid gameId;

};

#endif // QUEUEMANAGER_H
