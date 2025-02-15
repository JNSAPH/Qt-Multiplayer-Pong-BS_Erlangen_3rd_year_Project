#ifndef VIEW_WAITINGINQUEUE_H
#define VIEW_WAITINGINQUEUE_H

#include <QDialog>

#include "../utils/websocketclient.h"
#include "../Views/view_multiplayer.h"

namespace Ui {
class view_waitingInQueue;
}

class view_waitingInQueue : public QDialog
{
    Q_OBJECT

public:
    static view_waitingInQueue* getInstance();
    void startGame();
    ~view_waitingInQueue();

private:
    Ui::view_waitingInQueue *ui;
    explicit view_waitingInQueue(QWidget *parent = nullptr);
    static view_waitingInQueue* m_instance;
    QString m_ip = "85.214.124.142";
    QString m_port = "1215";
};

#endif // VIEW_WAITINGINQUEUE_H
