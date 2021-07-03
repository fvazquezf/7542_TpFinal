#include "MapListWindow.h"
#include "ui_MapListWindow.h"

MapListWindow::MapListWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapListWindow)
{
    styler.setCounterStrikeFont(this, 14);
    this->setWindowTitle("Counter Strike 2D");
    ui->setupUi(this);
}


MapListWindow::~MapListWindow() {
    delete ui;
}
