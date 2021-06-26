#include "QEditorMapWidget.h"
#define QTILE_SIZE 32
#define PATH_TO_MAPS "../maps/"
#include <QtDebug>

QEditorMapWidget::QEditorMapWidget (QWidget* parent, int rows, int columns, std::string &map_name) :
        QWidget (parent), rows(rows), columns(columns), map_name(map_name)
    {
        this->setMapLayout();
        this->setEmptyTilesLayout();
        this->setTileFromFile();
    }

void QEditorMapWidget::setMapLayout() {
    layout = new QGridLayout (this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
}

void QEditorMapWidget::setEmptyTilesLayout() {
    /*
    for (int column = 0; column < columns; column++) {
        for (int row = 0; row < rows; row++) {
            QIcon icon(":/resources/img/wall.png");
            QTile* tile = new QTile(this, QTILE_SIZE, QTILE_SIZE, icon);
            tiles[column][row] = tile;
            layout->addWidget(tile, row, column);
        }
    }*/
}

void QEditorMapWidget::loadFile() {
    std::string path = PATH_TO_MAPS + map_name + ".yml";
    try{
        qDebug() <<  QString::fromStdString(path);
        map_config = YAML::LoadFile(path);
    } catch (YAML::BadFile ex) {
        std::ofstream createFile { path };
        map_config = YAML::LoadFile(path);
    }
}

void QEditorMapWidget::setTileFromFile() {

    this->loadFile();
    std::vector<std::vector<int>> pos = map_config["wall"].as<std::vector<std::vector<int>>>();

    std::string text = map_config["prueba"].as<std::string>();
    qDebug() <<  QString::fromStdString(text);

    for (unsigned long i = 0; i< pos.size(); i ++) {
        int row = pos[i][0];
        int column = pos[i][1];
        QIcon icon(":/resources/img/wall.png");
        QTile* tile = new QTile(this, QTILE_SIZE, QTILE_SIZE, icon);
        tiles[column][row] = tile;
        layout->addWidget(tile, row, column);
    }

}
