#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include "Views/view_waitinginqueue.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MenuWindow; }
QT_END_NAMESPACE

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private slots:
    void on_btnQuitGame_clicked();

    void on_btnMultiplayer_clicked();

private:
    Ui::MenuWindow *ui;
    view_waitingInQueue *QueueWindow;
};
#endif // MENUWINDOW_H
