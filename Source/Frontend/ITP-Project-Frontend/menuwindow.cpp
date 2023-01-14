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

    qDebug() << "Clicked Mutliplayer";

    // Create Queue Window
    view_waitingInQueue* QueueWindow = view_waitingInQueue::getInstance();
    QueueWindow->show();
}
