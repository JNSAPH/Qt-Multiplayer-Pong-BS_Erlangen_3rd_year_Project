#include "view_finalscore.h"
#include "ui_view_finalscore.h"

view_FinalScore::view_FinalScore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::view_FinalScore)
{
    ui->setupUi(this);

    this->setFixedSize(QSize(680, 540));
    ui->imgWinner->hide();

    // Create a new instance of the HttpRequest class
    HttpRequest* request = HttpRequest::instance();

    // Define the URL and headers
    QString url = "http://localhost:1216/getScore";
    QMap<QByteArray, QByteArray> headers;

    // Send the GET request
    request->get(url, headers);

    // Connect to the readyRead signal of the QNetworkReply object, print the response data to the console, and call setTopScores()
    QObject::connect(request->getReply(), &QNetworkReply::readyRead, [request, this]() {
        if (request->getReply() == nullptr) {
            qDebug() << "Error: QNetworkReply is null";
            return;
        }
        QByteArray response = request->getReply()->readAll();
        setTopScores(response);
    });

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

void view_FinalScore::setTopScores(QByteArray jsonStr) {
    // Parse the JSON string
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray top5ScoresArr = jsonObj["Top5Scores"].toArray();


    // Assign the scores to the labels
    for (int i = 0; i < top5ScoresArr.size(); i++) {
        QJsonObject scoreObj = top5ScoresArr[i].toObject();
        QString playerId = scoreObj["PlayerID"].toString();
        QString score = scoreObj["Score"].toString();

        if (i == 0) {
            ui->score1->setText("1. " + playerId + ": " + score);
        } else if (i == 1) {
            ui->score2->setText("2. " + playerId + ": " + score);
        } else if (i == 2) {
            ui->score3->setText("3. " + playerId + ": " + score);
        } else if (i == 3) {
            ui->score4->setText("4. " + playerId + ": " + score);
        } else if (i == 4) {
            ui->score5->setText("5. " + playerId + ": " + score);
        }
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

