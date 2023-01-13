#include "view_multiplayer.h"
#include "ui_view_multiplayer.h"

view_multiplayer::view_multiplayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::view_multiplayer)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(680, 540));

    // Start Time for movement
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &view_multiplayer::movePlayer);
    timer->start(50); // move the player every 50ms

}

view_multiplayer::~view_multiplayer()
{
    delete ui;
}

void view_multiplayer::movePlayer() {
    QRect currentGeometry = ui->playerChar->geometry();

    int MIN_X = 100;
    int MAX_X = 580;
    int PX_MOVE = 10;

    if(A_key_pressed) {
        int newX = currentGeometry.x() - PX_MOVE;
        if (newX >= MIN_X && newX + currentGeometry.width() <= MAX_X) {
            currentGeometry.moveTo(newX, currentGeometry.y());
            ui->playerChar->setGeometry(currentGeometry);
        }
    }

    if(D_key_pressed) {
        int newX = currentGeometry.x() + PX_MOVE;
        if (newX >= MIN_X && newX + currentGeometry.width() <= MAX_X) {
            currentGeometry.moveTo(newX, currentGeometry.y());
            ui->playerChar->setGeometry(currentGeometry);
        }
    }
}

void view_multiplayer::playerShoot() {
    // Create a new QLabel object with the text "o" and add it to the main window
    QLabel* bullet = new QLabel("o", this);

    // Set the position of the bullet to be in the center of the playerChar object
    bullet->setGeometry(ui->playerChar->x() + ui->playerChar->width()/2, ui->playerChar->y(), 10, 10);

    // Show the bullet
    bullet->show();

    // Create a new QPropertyAnimation object for the bullet
    QPropertyAnimation* animation = new QPropertyAnimation(bullet, "geometry");

    animation->setDuration(1000); // Set Duration

    // Set the start value of the animation to be the current geometry of the bullet
    animation->setStartValue(bullet->geometry());

    // Set the end value of the animation to be a new QRect at the top of the screen
    animation->setEndValue(QRect(bullet->x(), 0, bullet->width(), bullet->height()));

    animation->start(); // Start the animation

    // Connect the finished signal of the animation to a lambda function that deletes the bullet
    QObject::connect(animation, &QPropertyAnimation::finished, [bullet](){
        bullet->deleteLater();
    });

}

void view_multiplayer::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        case Qt::Key_A: A_key_pressed = true; break;
        case Qt::Key_D: D_key_pressed = true; break;
        case Qt::Key_W: this->playerShoot(); break;
        case Qt::Key_Escape: QCoreApplication::quit(); break;
    }
}

void view_multiplayer::keyReleaseEvent(QKeyEvent * event) {
    switch(event->key()) {
        case Qt::Key_A: A_key_pressed = false; break;
        case Qt::Key_D: D_key_pressed = false; break;
    }
}
