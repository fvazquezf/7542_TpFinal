#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Q_INIT_RESOURCE(resource);
    ui->setupUi(this);
    this->setStart();
}

void MainWindow::handleStartPushButton() {
    MapConfigWindow* window = new MapConfigWindow(this);
    window->show();
}

void MainWindow::setStart() {
    QVBoxLayout* mainLayout = new QVBoxLayout();

    /*
    QMediaPlayer* player = new QMediaPlayer;

    QMediaPlaylist* playlist = new QMediaPlaylist(player);
    playlist->addMedia(QUrl("http://example.com/myclip1.mp4"));

    QVideoWidget* videoWidget = new QVideoWidget();
    player->setVideoOutput(videoWidget);
    videoWidget->show();
    playlist->setCurrentIndex(1);
    player->play();
*/
    QPushButton *startPushButton = new QPushButton("Start", this);
    mainLayout->addWidget(startPushButton,3);
    connect(startPushButton, SIGNAL (released()), this, SLOT (handleStartPushButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
    window()->close();
}
