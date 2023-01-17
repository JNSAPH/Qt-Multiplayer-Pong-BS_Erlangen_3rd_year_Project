#ifndef VIEW_MULTIPLAYER_H
#define VIEW_MULTIPLAYER_H

#include <QDialog>
#include <QWidget>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QTimer>

#include "../gameManager/gamestate.h"
#include "../gameManager/playermanager.h"

namespace Ui {
class view_multiplayer;
}

class view_multiplayer : public QDialog
{
    Q_OBJECT

public:
    explicit view_multiplayer(QWidget *parent = nullptr);
    void updatePlayingField();
    ~view_multiplayer();

protected:


private:
    Ui::view_multiplayer *ui;
    PlayerManager *m_playerManager;
    GameState *m_state;

};

#endif // VIEW_MULTIPLAYER_H
