#ifndef VIEW_MULTIPLAYER_H
#define VIEW_MULTIPLAYER_H

#include <QDialog>
#include <QWidget>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QTimer>

#include <thread>
#include <QThread>

#include "../utils/HttpRequest.h"


namespace Ui {
class view_multiplayer;
}

class view_multiplayer : public QDialog
{
    Q_OBJECT

public:
    explicit view_multiplayer(QWidget *parent = nullptr);
    ~view_multiplayer();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    Ui::view_multiplayer *ui;
    bool A_key_pressed;
    bool D_key_pressed;
    void movePlayer();
    void playerShoot();
public slots:
    void onResult();
};

#endif // VIEW_MULTIPLAYER_H
