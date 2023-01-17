#ifndef PLAYERCOMMUNICATIONMANAGER_H
#define PLAYERCOMMUNICATIONMANAGER_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>

/**
 * @class playerCommunicationManager
 * @brief  The playerCommunicationManager class handles the communication between players.
 *
 * This class listens to incoming text messages and interprets the data to determine the action that needs to be taken.
 * It then calls the appropriate function in the game class to carry out the action.
 */
class playerCommunicationManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the playerCommunicationManager class
     * @param parent The parent QObject
     */
    explicit playerCommunicationManager(QObject *parent = nullptr);

public slots:
    /**
     * @brief Slot that is called when a text message is received
     * @param message The received message
     */
    void onTextMessageReceived(const QString &message);
};

#endif // PLAYERCOMMUNICATIONMANAGER_H
