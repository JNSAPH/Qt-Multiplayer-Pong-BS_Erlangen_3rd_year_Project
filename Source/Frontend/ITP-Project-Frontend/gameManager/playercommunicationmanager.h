
#ifndef PLAYERCOMMUNICATIONMANAGER_H
#define PLAYERCOMMUNICATIONMANAGER_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>

#include "../Views/view_multiplayer.h"

#include "../gameManager/playermanager.h"
#include "../gameManager/gamestate.h"

class view_waitingInQueue;

class playerCommunicationManager : public QObject
{
    Q_OBJECT

public:
    playerCommunicationManager(QObject *parent = nullptr);

public slots:
    void onTextMessageReceived(const QString &message);
private:
    GameState *gameState;
    view_multiplayer *MultiplayerView;

};

#endif // PLAYERCOMMUNICATIONMANAGER_H
