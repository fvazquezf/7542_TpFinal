#include "MapCreationWindow.h"
#include "MapEditor.h"
#include "ui_MapCreationWindow.h"
#include <QLineEdit>
#include <QDebug>
#include <QFontDatabase>

MapCreationWindow::MapCreationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapCreationWindow)
{
    QFontDatabase::addApplicationFont(":/fonts/counter_strike.ttf");
    QFont CounterStrikeFont("Counter-Strike", 12, QFont::Normal);
    this->setFont(CounterStrikeFont);
    ui->setupUi(this);
}

MapCreationWindow::~MapCreationWindow()
{
    delete ui;
}

void MapCreationWindow::on_continueButton_clicked()
{
    this->mapName = ui->mapNameLineEdit->text();
    this->mapSize = ui->mapSizeComboBox->itemText(ui->mapSizeComboBox->currentIndex());
    if(this->mapName == "") {
        return;
    }
    qDebug() << "Map name: " << this->mapName;
    qDebug() << "Map size: " << this->mapSize;

    this->close();
    MapEditor mapEditor;
    mapEditor.setWindowTitle("Counter Strike 2D - Map editor");
    mapEditor.exec();

}

void MapCreationWindow::on_backButton_clicked()
{
    this->close();
}
