#include "MapListWindow.h"
#include "ui_MapListWindow.h"
#include <QFontDatabase>

MapListWindow::MapListWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapListWindow)
{
    QFontDatabase::addApplicationFont(":/fonts/counter_strike.ttf");
    QFont CounterStrikeFont("Counter-Strike", 12, QFont::Normal);
    this->setFont(CounterStrikeFont);
   ui->setupUi(this);
}


MapListWindow::~MapListWindow()
{
    delete ui;
}
