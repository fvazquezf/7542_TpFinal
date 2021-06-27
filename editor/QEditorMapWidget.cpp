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

void QEditorMapWidget::setTileFromFile(std::string &element) {
    std::vector<std::vector<int>> pos = map_config[element].as<std::vector<std::vector<int>>>();
    for (unsigned long i = 0; i< pos.size(); i ++) {
        int row = pos[i][0];
        int column = pos[i][1];
        QIcon icon = icons.getIcon(element);
        QTile* tile = new QTile(this, QTILE_SIZE, QTILE_SIZE, icon);
        tiles[column][row] = tile;
        layout->addWidget(tile, row, column);
    }

}
void QEditorMapWidget::setTileFromFile() {

    this->loadFile();
    std::vector<std::string> elements = map_config["elements"].as<std::vector<std::string>>();
    for (unsigned long i = 0; i< elements.size(); i ++) {
        qDebug() <<  "ELEMENT: " << QString::fromStdString(elements[i]);
        this->setTileFromFile(elements[i]);
    }
}
