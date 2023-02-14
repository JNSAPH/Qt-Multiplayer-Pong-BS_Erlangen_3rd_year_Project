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
    static void addScore(QString playerId, int score);
    static void updateName(QString playerId, QString playerName);
    static QList<QStringList> getScore();
};

#endif // SCORE_H
