#ifndef VIEW_WAITINGINQUEUE_H
#define VIEW_WAITINGINQUEUE_H

#include <QDialog>

#include "../Controller/wsocketcontroller.h"
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
};

#endif // VIEW_WAITINGINQUEUE_H
