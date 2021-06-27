#ifndef QEDITOR_MAP_WIDGET_H
#define QEDITOR_MAP_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include "QTile.h"
#include "yaml-cpp/yaml.h"
#include <fstream>
#include "MapIconGenerator.h"

#define MAX_ROWS 1000
#define MAX_COLUMNS 1000

class QEditorMapWidget : public QWidget {
    Q_OBJECT

public:

    QEditorMapWidget (QWidget* parent, int rows, int columns, std::string &map_name);
    void setItem(std::string &item);
private slots:
    void handleItemSelection(std::string &selectedItem);

private:
    const int rows;
    const int columns;
    QTile* tiles[MAX_COLUMNS][MAX_ROWS];
    QGridLayout* layout;
    std::string map_name;
    YAML::Node map_config;
    MapIconGenerator icons;
    std::string selectedItem;

    void setMapLayout();
    void setTileFromFile();
    void setTileFromFile(std::string &element);
    void loadFile();
};

#endif   //QEDITOR_MAP_WIDGET_H
