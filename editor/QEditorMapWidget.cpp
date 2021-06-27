#include "QEditorMapWidget.h"
#define QTILE_SIZE 32
#define PATH_TO_MAPS "../maps/"
#include <QtDebug>
#include <exception>

QEditorMapWidget::QEditorMapWidget (QWidget* parent, int rows, int columns, std::string &map_name) :
        QWidget (parent), rows(rows), columns(columns), map_name(map_name)
    {
        this->setMapLayout();
        this->setTileFromFile();
        this->resize(rows * QTILE_SIZE, columns * QTILE_SIZE);
    }

void QEditorMapWidget::setMapLayout() {
    layout = new QGridLayout (this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    this->setLayout(layout);
}

void QEditorMapWidget::loadFile() {
    std::string path = PATH_TO_MAPS + map_name + ".yml";
    try{
        map_config = YAML::LoadFile(path);
    } catch (YAML::BadFile ex) {
        std::ofstream createFile { path };
        map_config = YAML::LoadFile(path);
    }
}

void QEditorMapWidget::updateFile() {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; i < columns; j++) {
            // TO-DO
        }
    }
}

void QEditorMapWidget::addQTile(std::string &element, int row, int column) {
    QIcon icon = icons.getIcon(element);
    QTile* tile = new QTile(this, QTILE_SIZE, QTILE_SIZE, icon);
    //tiles[column][row] = element;
    layout->addWidget(tile, row, column);
}

void QEditorMapWidget::setTileFromFile(std::string &element) {
    std::vector<std::vector<int>> pos = map_config[element].as<std::vector<std::vector<int>>>();
    for (unsigned long i = 0; i< pos.size(); i ++) {
        this->addQTile(element, pos[i][0], pos[i][1]);
    }
}

void QEditorMapWidget::setTileFromFile() {

    this->loadFile();
    std::vector<std::string> elements = map_config["elements"].as<std::vector<std::string>>();
    for (unsigned long i = 0; i< elements.size(); i ++) {
        this->setTileFromFile(elements[i]);
    }
}

void QEditorMapWidget::setItem(std::string &item) {
    this->selectedItem = item;
}

void QEditorMapWidget::mousePressEvent(QMouseEvent *event) {
    if(event->type() == QMouseEvent::MouseButtonPress) {
        QPoint pos = event->pos();
        int row = pos.y() / QTILE_SIZE;
        int column = pos.x() / QTILE_SIZE;
        this->addQTile(this->selectedItem, row, column);
    }
}
