#ifndef VIEW_FINALSCORE_H
#define VIEW_FINALSCORE_H

#include <QDialog>
#include <QApplication>
#include <QProcess>

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

private:
    Ui::view_FinalScore *ui;
};

#endif // VIEW_FINALSCORE_H
