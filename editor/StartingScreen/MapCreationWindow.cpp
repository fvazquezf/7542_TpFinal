#include "MapCreationWindow.h"
#include "MapEditor.h"
#include "ui_MapCreationWindow.h"
#include <QLineEdit>
#include <QDebug>
#include <QFontDatabase>
#include <QMessageBox>
#define PATH_TO_MAPS "../../maps/"
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
        QMessageBox::warning(this, tr("Map creation"),
                             tr("The map must have a name."),
                             QMessageBox::Close);
        return;
    }
    qDebug() << "Map name: " << this->mapName;
    qDebug() << "Map size: " << this->mapSize;

    this->close();
    MapEditor mapEditor;
    std::string path_to_map = PATH_TO_MAPS + this->mapName.toStdString() +".yml";
    mapEditor.loadMap(path_to_map);
    mapEditor.show();
    mapEditor.exec();

}

void MapCreationWindow::on_backButton_clicked()
{
    this->close();
}
