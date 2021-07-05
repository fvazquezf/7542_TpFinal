#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setStart();
}

void MainWindow::handleStartPushButton() {
    MapConfigWindow* window = new MapConfigWindow(this);
    window->show();
}

void MainWindow::setStart() {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QPushButton *startPushButton = new QPushButton("Start", this);
    mainLayout->addWidget(startPushButton,3);
    connect(startPushButton, SIGNAL (released()), this, SLOT (handleStartPushButton()));
}

MainWindow::~MainWindow()
{
    window()->close();
}
