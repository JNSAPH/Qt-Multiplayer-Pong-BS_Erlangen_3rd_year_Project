#include "playercommunicationmanager.h"

#include "../Views/view_waitinginqueue.h"
#include "../gameManager/playermanager.h"


playerCommunicationManager::playerCommunicationManager(QObject *parent) : QObject(parent){
    gameState = &GameState::getInstance();
    MultiplayerView = new view_multiplayer();
    FinalScoreView = new view_FinalScore();
}


void playerCommunicationManager::onTextMessageReceived(const QString &message)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject jsonObject = jsonDoc.object();

    switch (jsonObject["code"].toInt()) {
    case 200:
        // Player Joined
        PlayerManager::getInstance().setPlayerNumber(jsonObject["PlayerNumber"].toInt());
        PlayerManager::getInstance().setUUID(jsonObject["UUID"].toString());
        break;
    case 201:
        // Game is stating
        qDebug() << "Game is starting";
        view_waitingInQueue::getInstance()->hide();
        MultiplayerView->setPaddleColor();
        MultiplayerView->show();

        break;
    case 203:
        // Player Left
        qDebug() << "Player left";
        break;
    case 204:
        // Game state Update
        gameState->setRunning(jsonObject["running"].toBool());
        gameState->setScore1(jsonObject["score1"].toInt());
        gameState->setScore2(jsonObject["score2"].toInt());

        gameState->setPaddle1(
                jsonObject["paddle1"].toObject()["x"].toDouble(),
                jsonObject["paddle1"].toObject()["y"].toDouble(),
                jsonObject["paddle1"].toObject()["width"].toDouble(),
                jsonObject["paddle1"].toObject()["height"].toDouble()
            );
        gameState->setPaddle2(
                jsonObject["paddle2"].toObject()["x"].toDouble(),
                jsonObject["paddle2"].toObject()["y"].toDouble(),
                jsonObject["paddle2"].toObject()["width"].toDouble(),
                jsonObject["paddle2"].toObject()["height"].toDouble()
                );

        gameState->setBall(
                jsonObject["ball"].toObject()["vx"].toDouble(),
                jsonObject["ball"].toObject()["vy"].toDouble(),
                jsonObject["ball"].toObject()["x"].toDouble(),
                jsonObject["ball"].toObject()["y"].toDouble(),
                jsonObject["ball"].toObject()["radius"].toDouble()
            );

        // Call Playing field update in view_multiplayer;
        MultiplayerView->updatePlayingField();
        break;
    case 999:
        MultiplayerView->close();
        FinalScoreView->show();
        FinalScoreView->finalWinner(jsonObject["winner"].toInt(), PlayerManager::getInstance().getPlayerNumber());
        break;
    }
}
