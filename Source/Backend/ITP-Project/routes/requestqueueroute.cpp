#include "requestqueueroute.h"

RequestQueueRoute::RequestQueueRoute() { }

/*
 * Method: POST
 * Route: /api/requestQueue
 * Response: JSON
 */
void RequestQueueRoute::handleRoute(QTcpSocket *socket, const QMap<QString, QString> &parameters)
{
    int playerId = parameters["userId"].toInt();
    std::string response;

    try {
        // Player should connect to webSocket before making this Request
        QueueManager::addPlayer(playerId);


        QUuid gameId = QueueManager::getGameId();
        if(!gameId.isNull()) {
            qDebug() << "Game can start!";
            // emit webSocket Event to notify Players the game is starting
        }


        std::map<std::string, JSONUtils::Value> data{
          {"code", 200},
          {"message", "Added to the Queue"},
          {"gameId_created", !gameId.isNull()}
        };

        // Generate Response
        response = WSUtils::createJSONResponse(JSONUtils::generateJSON(data));
    } catch (QueueFullException& e) {
        // Queue is full
        std::map<std::string, JSONUtils::Value> data{
          {"code", 400},
          {"message", e.what()}
        };

        // Generate Response
        response = WSUtils::createJSONResponse(JSONUtils::generateJSON(data));
    }

    // Send Response
    socket->write(response.c_str());
    socket->close();

}
