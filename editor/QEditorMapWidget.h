#ifndef QEDITOR_MAP_WIDGET_H
#define QEDITOR_MAP_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include "QTile.h"
#include "yaml-cpp/yaml.h"
#include <fstream>
#include <QMouseEvent>
#include "MapIconGenerator.h"
#include <algorithm>
#include <utility>
#include "constantes.h"

class QEditorMapWidget : public QWidget {
    Q_OBJECT

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

public:
    QEditorMapWidget (QWidget* parent, std::string &map_name, int rows, int columns);
    QEditorMapWidget (QWidget* parent, std::string &map_name);
    void setItem(std::string &item);
    void updateMapLFile();

private:
    QGridLayout* layout;
    std::map<std::string, std::list<std::list<int>>> tiles;
    std::map<std::pair<int,int>, std::string> positions;
    std::map<std::string, int> size;
    std::vector<std::string> elements = {
        "wall_1", "wall_2", "wall_3", "wall_4", "wall_5", "wall_6", "wall_7", "wall_8",
        "zoneA", "zoneB", "zoneBomb",
        "bomb", "m3", "AK-47", "knife", "glock", "AWP"};

    std::string map_name;
    MapIconGenerator icons;
    std::string selectedItem;
    std::string selectedBackground = "aztec";

    void setMapLayout();

    void setTilesBackGround();
    void setTilesFromOldFile();
    void setTilesFromNewFile();

    void loadNewFile(int rows, int columns);
    void loadOldFile();

    void addQTile(std::string &element, int row, int column);

};

#endif   //QEDITOR_MAP_WIDGET_H
