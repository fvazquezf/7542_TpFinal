#include "QTile.h"

QTile::QTile (QWidget *parent, int width, int height, QPixmap &pixmap) :
    QLabel (parent) {
    this->setPixmap(pixmap);
    this->setEditorMapStyle(width, height);
}

void QTile::setEditorMapStyle(int width, int height) {

    this->setFixedSize(QSize(width, height));
}
