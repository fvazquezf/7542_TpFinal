#include "QEditorMapListWidget.h"
#include <QDebug>
#include <common/Protocol.h>

QEditorMapListWidget::QEditorMapListWidget(QWidget *parent, int width, int height, LogInInfo &info)
    : QListWidget(parent),
      info(info){
    this->doAutoScroll();
    this->scrollBarWidgets(Qt::AlignRight);
    this->setMapItems();
}

void QEditorMapListWidget::setMapItems() {
    this->update();
}

void QEditorMapListWidget::setMapItem(QString &mapName) {
    QListWidgetItem* item = new QListWidgetItem();
    item->setText(mapName);
    this->addItem(item);
}


void QEditorMapListWidget::update() {
    /*this->clear();
    QDir directory(DIRECTORY_PATH);
    QStringList mapsList  = directory.entryList();
    for (QString& mapName : mapsList) {
        if(mapName != "." && mapName != "..") {
            mapName.chop(4);
            this->addItem(mapName);
        }
    }*/
    auto gamesList = info.receiveGameInformation();
    for (auto& game : gamesList){
        this->addItem(QString::fromUtf8( game.data(), game.size()));
    }
}

