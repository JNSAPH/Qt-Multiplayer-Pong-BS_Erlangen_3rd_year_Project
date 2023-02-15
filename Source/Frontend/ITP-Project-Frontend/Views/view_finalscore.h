#ifndef VIEW_FINALSCORE_H
#define VIEW_FINALSCORE_H

#include <QDialog>
#include <QApplication>
#include <QProcess>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "./utils/HttpRequest.h"
#include "../gameManager/playermanager.h"

namespace Ui {
class view_FinalScore;
}

class view_FinalScore : public QDialog
{
    Q_OBJECT

public:
    explicit view_FinalScore(QWidget *parent = nullptr);
    ~view_FinalScore();
    void finalWinner(int winnerPlayerNumber, int clientPlayerNumber);

private slots:
    void on_btnQuit_clicked();

    void on_btnPlayAgain_clicked();

    void on_userBtn_clicked();

private:
    Ui::view_FinalScore *ui;
    void pingForScores();
    void setTopScores(QByteArray jsonStr);
    void setUsername();
    QString m_ip = "85.214.124.142";
    QString m_port = "1216";
};

#endif // VIEW_FINALSCORE_H
