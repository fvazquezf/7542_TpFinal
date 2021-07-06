#include "QTile.h"

QTile::QTile (QWidget *parent, int width, int height, QIcon &icon) :
    QLabel (parent), icon(icon) {
    this->setPixmap(icon.pixmap(QSize(width, height)));
    this->setEditorMapStyle(width, height);
}

void QTile::setEditorMapStyle(int width, int height) {

    this->setFixedSize(QSize(width, height));
}
