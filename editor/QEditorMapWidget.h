#ifndef QEDITOR_MAP_WIDGET_H
#define QEDITOR_MAP_WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include "QTile.h"
#include "yaml-cpp/yaml.h"
#include <fstream>
#include <QMouseEvent>
#include "MapQPixmapGenerator.h"
#include <algorithm>
#include <utility>
#include "constantes.h"
#include "Elements.h"
#include "ZoneValidator.h"
#include <iostream>

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
    bool hasValidZones();
private:
    QGridLayout* layout;
    std::map<std::pair<int,int>, std::string> positions;
    std::map<std::string, int> size;

    Elements e;
    ZoneValidator zoneValidator;
    MapQPixmapGenerator pixmaps;

    std::string map_name;
    std::string selectedItem;
    std::string selectedBackground = "aztec";

    void setMapLayout();

    void setTilesBackGround();
    void updateBackGround();
    void setTilesFromOldFile();
    void setTilesFromNewFile();

    void loadNewFile(int rows, int columns);
    void loadOldFile();

    void _addQTile(std::string &element, int row, int column);
    void addQTile(std::string &element, int row, int column);
    void removeQTile(int row, int column);
    void resetZone(std::string &element);


};

#endif   //QEDITOR_MAP_WIDGET_H
