#include "score.h"

void Score::addScore(QString playerId, int score) {
    QString timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);
    QString scoreStr = QString("%1,%2,%3,%4\n").arg(playerId).arg("Guest").arg(score).arg(timestamp);
    QFile file("Score.csv");
    if (!file.exists()) {
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream stream(&file);
        stream << "PlayerID,PlayerName,Score,Timestamp\n";
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
            if (fields.size() >= 4) {
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

void Score::updateName(QString playerId, QString playerName) {
    QFile file("Score.csv");
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream stream(&file);
        QString header = stream.readLine();
        QStringList headers = header.split(",");
        int idIndex = headers.indexOf("PlayerID");
        int nameIndex = headers.indexOf("PlayerName");
        int scoreIndex = headers.indexOf("Score");
        int timestampIndex = headers.indexOf("Timestamp");
        bool found = false;
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            QStringList values = line.split(",");
            if (values[idIndex] == playerId) {
                found = true;
                values[nameIndex] = playerName;
                stream.seek(stream.pos() - line.length() - 1); // go back to beginning of line
                stream << values.join(",") << '\n'; // overwrite the line with the new values
                break;
            }
        }
        if (!found) {
            qWarning() << "Player with ID " << playerId << " not found in Score.csv";
        }
        file.close();
    } else {
        qWarning() << "Failed to open Score.csv";
    }
}
