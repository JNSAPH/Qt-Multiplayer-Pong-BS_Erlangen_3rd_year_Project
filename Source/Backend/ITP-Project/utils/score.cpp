#include "score.h"

void Score::addScore(QString playerId, int score) {
    QString timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);
    QString scoreStr = QString("%1,%2,%3\n").arg(playerId).arg(score).arg(timestamp);
    QFile file("Score.csv");
    if (!file.exists()) {
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream stream(&file);
        stream << "PlayerID,Score,Timestamp\n";
        file.close();
    }
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << scoreStr;
        file.close();
    } else {
        qWarning() << "Failed to open Score.csv";
    }
}

QList<QStringList> Score::getScore() {
    QList<QStringList> data;
    QFile file("Score.csv");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        QString header = stream.readLine();
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            QStringList fields = line.split(",");
            if (fields.size() >= 3) {
                data.append(fields);
            }
        }
        file.close();
    } else {
        qWarning() << "Failed to open Score.csv";
    }
    std::sort(data.begin(), data.end(), [](const QStringList& a, const QStringList& b) {
        return a.at(1).toInt() > b.at(1).toInt();
    });
    return data;
}
