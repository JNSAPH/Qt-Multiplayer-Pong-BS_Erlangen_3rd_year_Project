#include "GetScoreRoute.h"

GetScoreRoute::GetScoreRoute() { }

void GetScoreRoute::handleRoute(QTcpSocket *socket, const QMap<QString, QString> &parameters)
{
    // Prepare JSON Map for Dat
    QJsonArray jsonArray;
    QList<QStringList> data = Score::getScore();
    int count = 0;
    for (const auto& row : data) {
        QJsonObject jsonObject;
        jsonObject["PlayerID"] = row[0];
        jsonObject["Score"] = row[1];
        jsonArray.append(jsonObject);
        count++;
        if (count >= 5) {
            break;
        }
    }
    QJsonObject topLevelObject;
    topLevelObject["Top5Scores"] = jsonArray;
    QJsonDocument jsonDocument(topLevelObject);

    std::string response = WSUtils::createJSONResponse(jsonDocument.toJson().toStdString());

    socket->write(response.c_str());
    socket->close();
}
