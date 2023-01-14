#include "menuwindow.h"
#include "ui_menuwindow.h"

MenuWindow::MenuWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(680, 540));
}

MenuWindow::~MenuWindow()
{
    delete ui;
}


void MenuWindow::on_btnQuitGame_clicked()
{
    QCoreApplication::quit();
}


void MenuWindow::on_btnMultiplayer_clicked()
{
    // Close current Window
    this->close();

    // Create Multiplayer Window
    QueueWindow = new view_waitingInQueue(this);
    QueueWindow->show();
}

void MenuWindow::showMultiplayer() {
    // Close current Window
    this->close();

    // Create Multiplayer Window
    MultiplayerWindow = new view_multiplayer(this);
    MultiplayerWindow->show();
}
