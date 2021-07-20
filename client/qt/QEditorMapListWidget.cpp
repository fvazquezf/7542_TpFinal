#include "QEditorMapListWidget.h"
#include <QDebug>
#include <common/Protocol.h>

QEditorMapListWidget::QEditorMapListWidget(QWidget *parent, int width, int height, LogInInfo &info)
    : QListWidget(parent),
      info(info) {
    this->doAutoScroll();
    this->scrollBarWidgets(Qt::AlignRight);
    this->setMapItems();
}

void QEditorMapListWidget::setMapItems() {
    this->update();
}

void QEditorMapListWidget::update() {
    std::vector<std::string> gamesList;
    try {
        gamesList = info.receiveGameInformation();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        info.failed = true;
        return;
    }
    for (auto& game : gamesList) {
        this->addItem(QString::fromUtf8( game.data(), game.size()));
    }
}

