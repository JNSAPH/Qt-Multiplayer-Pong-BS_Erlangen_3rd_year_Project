#include "playercommunicationmanager.h"
#include "../Pong/game.h"

playerCommunicationManager::playerCommunicationManager(QObject *parent) : QObject(parent){ }

void playerCommunicationManager::onTextMessageReceived(const QString &message)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject jsonObject = jsonDoc.object();

    QString action;
    int player;

    qDebug() << "GOT MESSAGE";

    switch (jsonObject["code"].toInt()) {
        case 110:
            // Player Moved
            action = jsonObject["action"].toString();
            player = jsonObject["PlayerNumber"].toInt();

            if(player == 1) {
                // Player 1 Action
                if(action == "up") {
                    Game::getInstance().movePaddle1Up();
                } else if(action == "down") {
                    Game::getInstance().movePaddle1Down();
                }
            } else if (player == 2) {
                // Player 2 Action
                if(action == "up") {
                    Game::getInstance().movePaddle1Up();
                } else if(action == "down") {
                    Game::getInstance().movePaddle1Down();
                }
            }
            break;
        default:
            qDebug() << message;
        break;
    }
}

