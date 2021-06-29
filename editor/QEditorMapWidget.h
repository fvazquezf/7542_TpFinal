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
    QEditorMapWidget (QWidget* parent, std::string &map_name, int rows, int columns);
    QEditorMapWidget (QWidget* parent, std::string &map_name);
    void setItem(std::string &item);
    void updateMapLFile();

private:
    QGridLayout* layout;
    std::map<std::string, std::list<std::list<int>>> tiles;
    std::map<std::string, int> size;
    std::vector<std::string> elements = {"aztec", "zoneA", "zoneB", "zoneBomb", "bomb", "m3"};

    std::string map_name;
    MapIconGenerator icons;
    std::string selectedItem;

    void setMapLayout();

    void setTilesFromOldFile();
    void setTilesFromNewFile();

    void loadNewFile(int rows, int columns);
    void loadOldFile();

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
