#include "MapCreationWindow.h"
#include "MapEditor.h"
#include "ui_MapCreationWindow.h"
#include <QLineEdit>
#include <QDebug>
#include <QMessageBox>

#include "CounterStrikeStyle.h"
#define PATH_TO_MAPS "../maps/"
MapCreationWindow::MapCreationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapCreationWindow)
{
    styler.setCounterStrikeFont(this, 14);
    this->setWindowTitle("Counter Strike 2D - Configuration");
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
    MapEditor mapEditor(this, this->mapName.toStdString(), 15, 15);
    mapEditor.exec();
}

void MapCreationWindow::on_backButton_clicked()
{
    this->close();
}
