#include "view_multiplayer.h"
#include "ui_view_multiplayer.h"

view_multiplayer::view_multiplayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::view_multiplayer)
{
    ui->setupUi(this);
}

view_multiplayer::~view_multiplayer()
{
    delete ui;
}
