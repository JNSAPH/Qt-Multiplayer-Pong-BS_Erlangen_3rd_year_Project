#include "GetScoreRoute.h"

GetScoreRoute::GetScoreRoute() { }

void GetScoreRoute::handleRoute(QTcpSocket *socket, const QMap<QString, QString> &parameters)
{
    // Prepare JSON Map for Data
    QJsonArray jsonArray;
    QList<QStringList> data = Score::getScore();

    // Filter out empty lines
    /**
     * This is stupid and i need to figure out why it randomly adds lines with missing Rows.
     * It works tho :D
     */
    data.erase(std::remove_if(data.begin(), data.end(), [](const QStringList& fields) {
        return fields[0].isEmpty() || fields[1].isEmpty() || fields[2].isEmpty();
    }), data.end());

    // Sort data by score in descending order
    std::sort(data.begin(), data.end(), [](const QStringList& a, const QStringList& b) {
        return a[2].toInt() > b[2].toInt();
    });


    // Append top 5 scores to JSON array
    int count = 0;
    for (const auto& row : data) {
        QJsonObject jsonObject;
        jsonObject["PlayerID"] = row[0];
        jsonObject["PlayerName"] = row[1];
        jsonObject["Score"] = row[2];
        jsonArray.append(jsonObject);
        count++;
        if (count >= 5) {
            break;
        }
    }

    // Create JSON response
    QJsonObject topLevelObject;
    topLevelObject["Top5Scores"] = jsonArray;
    QJsonDocument jsonDocument(topLevelObject);
    std::string response = WSUtils::createJSONResponse(jsonDocument.toJson().toStdString());

    // Send response and close socket
    socket->write(response.c_str());
    socket->close();
}

