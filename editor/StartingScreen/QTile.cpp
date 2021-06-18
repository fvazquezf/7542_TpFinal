#include "QTile.h"
#include "ui_QTile.h"

QTile::QTile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QTile)
{
    ui->setupUi(this);
}

QTile::~QTile()
{
    delete ui;
}
