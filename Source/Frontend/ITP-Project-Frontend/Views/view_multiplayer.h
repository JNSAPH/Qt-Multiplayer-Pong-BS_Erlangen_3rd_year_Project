#ifndef VIEW_MULTIPLAYER_H
#define VIEW_MULTIPLAYER_H

#include <QDialog>

namespace Ui {
class view_multiplayer;
}

class view_multiplayer : public QDialog
{
    Q_OBJECT

public:
    explicit view_multiplayer(QWidget *parent = nullptr);
    ~view_multiplayer();

private:
    Ui::view_multiplayer *ui;
};

#endif // VIEW_MULTIPLAYER_H
