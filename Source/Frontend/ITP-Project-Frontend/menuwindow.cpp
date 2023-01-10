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
    // Create a new window here in which the game will take place.
    // Maybe add a "waiting room" view before sending both players into the real game
}

