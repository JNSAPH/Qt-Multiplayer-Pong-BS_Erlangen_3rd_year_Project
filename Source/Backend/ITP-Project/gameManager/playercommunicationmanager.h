#ifndef PLAYERCOMMUNICATIONMANAGER_H
#define PLAYERCOMMUNICATIONMANAGER_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>

class playerCommunicationManager : public QObject
{
    Q_OBJECT

public:
    explicit playerCommunicationManager(QObject *parent = nullptr);

public slots:
    void onTextMessageReceived(const QString &message);
};

#endif // PLAYERCOMMUNICATIONMANAGER_H
