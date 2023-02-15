#ifndef SCORE_H
#define SCORE_H

#include <QtCore/QList>
#include <QtCore/QStringList>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <algorithm>

class Score {
public:
    /**
     * @brief Adds a new score to the CSV file. If the specified player ID is already present
     * in the file, the score for that player is updated instead.
     *
     * @param playerId The ID of the player.
     * @param score The score to add for the player.
     */
    static void addScore(QString playerId, int score);

    /**
     * @brief Updates the name of a player in the CSV file.
     *
     * @param playerId The ID of the player.
     * @param playerName The new name for the player.
     */
    static void updateName(QString playerId, QString playerName);

    /**
     * @brief Gets a list of all scores in the CSV file, sorted by score in descending order.
     * Each score is represented as a list of strings in the format [playerId, playerName, score, timestamp].
     *
     * @return A list of all scores in the CSV file.
     */
    static QList<QStringList> getScore();
};


#endif // SCORE_H
