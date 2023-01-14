#ifndef VIEW_WAITINGINQUEUE_H
#define VIEW_WAITINGINQUEUE_H

#include <QDialog>

#include "../Controller/wsocketcontroller.h"

namespace Ui {
class view_waitingInQueue;
}

class view_waitingInQueue : public QDialog
{
    Q_OBJECT

public:
    explicit view_waitingInQueue(QWidget *parent = nullptr);
    ~view_waitingInQueue();

private:
    Ui::view_waitingInQueue *ui;
};

#endif // VIEW_WAITINGINQUEUE_H
