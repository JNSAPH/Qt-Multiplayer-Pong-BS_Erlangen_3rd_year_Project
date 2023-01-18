#include "view_finalscore.h"
#include "ui_view_finalscore.h"

view_FinalScore::view_FinalScore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::view_FinalScore)
{
    ui->setupUi(this);

    this->setFixedSize(QSize(680, 540));
    ui->imgWinner->hide();

    this->setWindowTitle("Multiplayer - Pong (ITP)");
}

view_FinalScore::~view_FinalScore()
{
    delete ui;
}

void view_FinalScore::finalWinner(int winnerPlayerNumber, int clientPlayerNumber) {
    qDebug() << winnerPlayerNumber;
    qDebug() << clientPlayerNumber;
    if(winnerPlayerNumber == clientPlayerNumber) {
        // Client won
        ui->imgWinner->show();
        ui->labelDisplayWinner->setText("You won!");
    } else {
        // Enemy won
        ui->labelDisplayWinner->setText("You lost!");
    }
}

void view_FinalScore::on_btnQuit_clicked()
{
    QCoreApplication::quit();
}


void view_FinalScore::on_btnPlayAgain_clicked()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

