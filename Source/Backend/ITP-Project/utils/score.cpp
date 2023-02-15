#include "score.h"

void Score::addScore(QString playerId, int score) {
    // Get the current timestamp
    QString timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);

    // Format the score as a string to be added to the CSV file
    QString scoreStr = QString("%1,%2,%3,%4\n").arg(playerId).arg("Guest").arg(score).arg(timestamp);

    // Open the CSV
    QFile file("Score.csv");

    // If the file doesn't exist, create it and add a header row
    if (!file.exists()) {
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream stream(&file);
        stream << "PlayerID,PlayerName,Score,Timestamp\n";
        file.close();
    }

    // Open the file in read-write mode
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {

        // Read the contents of the file into a QString
        QTextStream stream(&file);
        QString fileContents = stream.readAll();

        // Check if the player ID is already in the file
        int index = fileContents.indexOf(playerId);

        // PlayerID is already present in the file
        // Update the existing score

        // Split the file contents into lines
        if (index != -1) {
            // PlayerID is already present in the file
            // Update the existing score
            QStringList lines = fileContents.split('\n');

            // Iterate over the lines, skipping the header row and the last empty line
            for (int i = 1; i < lines.size() - 1; i++) {
                // Split the line into values
                QStringList values = lines[i].split(',');

                // If the player ID matches, update the score
                if (values[0] == playerId) {
                    // Get the current score for the player
                    int currentScore = values[2].toInt();

                    // Update the score by adding the new score to the existing score
                    lines[i] = QString("%1,%2,%3,%4").arg(playerId).arg("Guest").arg(currentScore + score).arg(timestamp);
                    break;
                }
            }

            // Join the lines back together into a single QString
            fileContents = lines.join('\n') + '\n';

            // Set the file position to the beginning and overwrite the contents of the file with the updated contents
            file.seek(0);
            stream << fileContents;

            // Truncate the file to the current position of the file pointer
            file.resize(file.pos());
        } else {
            // PlayerID is not present in the file
            // Append the new score to the end of the file

            // Set the file position to the beginning and append the new score string to the file
            stream.seek(0);
            stream << fileContents << scoreStr;

            // Truncate the file to the current position of the file pointer
            file.resize(file.pos());
        }
        // Close the file
        file.close();
    } else {
        // Failed to open the file
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
