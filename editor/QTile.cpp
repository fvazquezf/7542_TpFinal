#include "QTile.h"
#include <QString>

QTile::QTile (QWidget *parent, int width, int height, QIcon &icon) :
    QLabel (parent), icon(icon) {
    this->setPixmap(icon.pixmap(QSize(32, 32)));
    this->setEditorMapStyle(width, height);
}

void QTile::setEditorMapStyle(int width, int height) {

    this->setFixedSize(QSize(width, height));
}
