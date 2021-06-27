#ifndef QEDITOR_MAP_WIDGET_H
#define QEDITOR_MAP_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include "QTile.h"
#include "yaml-cpp/yaml.h"
#include <fstream>
#include <QMouseEvent>
#include "MapIconGenerator.h"

class QEditorMapWidget : public QWidget {
    Q_OBJECT

public:
    QEditorMapWidget (QWidget* parent, int rows, int columns, std::string &map_name);
    void setItem(std::string &item);
    void updateFile();

private:
    const int rows;
    const int columns;
    std::vector<std::vector<std::string>> tiles;
    QGridLayout* layout;
    std::string map_name;
    YAML::Node map_config;
    MapIconGenerator icons;
    std::string selectedItem;

    void setMapLayout();
    void setEmptyMap();
    void setTileFromFile();
    void setTileFromFile(std::string &element);
    void loadFile();
    void addQTile(std::string &element, int row, int column);
/*
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    */
    void mousePressEvent(QMouseEvent *event) override;
};

#endif   //QEDITOR_MAP_WIDGET_H
