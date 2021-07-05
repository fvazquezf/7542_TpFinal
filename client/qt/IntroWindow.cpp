#include "IntroWindow.h"
#include <unistd.h>
#include <QDir>
#include <QDebug>
#include <QHBoxLayout>

IntroWindow::IntroWindow(QWidget *parent, int width, int heigth) {
    playlist = new QMediaPlaylist;
    player = new QMediaPlayer;
    this->move(parent->pos());
    this->setFixedSize(width, heigth);
    this->setContentsMargins(0,0,0,0);
    this->setWindowTitle("Counter Strike 2D");
}

void IntroWindow::run(){
    QDir dir(QDir::currentPath());
    dir.cdUp();
    playlist->addMedia(QUrl::fromLocalFile(dir.path() + "/client/qt/resources/intro.mp4"));
    playlist->setCurrentIndex(1);
    player->setPlaylist(playlist);
    player->setVideoOutput(this);

    this->show();
    player->play();

    usleep(9 * 1000000);//sleeps for 3 second

    player->stop();
    this->close();
}

IntroWindow::~IntroWindow() {

}
