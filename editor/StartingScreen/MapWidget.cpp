#include "MapWidget.h"
#include "ui_MapWidget.h"
#include <QLabel>
MapWidget::MapWidget(QWidget *parent, std::string file_name) :
    QWidget(parent),
    ui(new Ui::MapWidget)
{
    this->file_name = file_name;
    this->setValues();
    ui->setupUi(parent);
}

void MapWidget::setValues() {
   //YAML::Node config = YAML::LoadFile("config.yaml");

}

MapWidget::~MapWidget()
{
    delete ui;
}
