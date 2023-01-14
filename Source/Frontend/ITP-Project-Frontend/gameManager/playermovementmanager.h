
#ifndef PLAYERMOVEMENTMANAGER_H
#define PLAYERMOVEMENTMANAGER_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>

class view_waitingInQueue;

class playerMovementManager : public QObject
{
    Q_OBJECT

public:
    explicit playerMovementManager(QObject *parent = nullptr);

public slots:
    void onTextMessageReceived(const QString &message);

};

#endif // PLAYERMOVEMENTMANAGER_H
