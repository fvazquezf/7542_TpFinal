#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QtWidgets>
#include <QDialog>
#include <QWidget>
#include <QBoxLayout>
#include <QLabel>

#include <stdlib.h>
#include <vector>
#include <fstream>
#include <list>

#include "yaml-cpp/yaml.h"

#include "QEditorMapWidget.h"
#include "QEditorItemsWidget.h"
#include "CounterStrikeStyle.h"
#include "constantes.h"

class MapEditor : public QDialog
{
    Q_OBJECT

public:
    explicit MapEditor(QWidget *parent, const std::string &name);
    explicit MapEditor(QWidget *parent, const std::string &name, int row, int column);
    ~MapEditor();

private slots:
    void handleSaveButton();
    void handleQuitButton();
    void treeClicked(QTreeWidgetItem* item, int column);

private:
    //Layouts
    QHBoxLayout *mainLayout;
    QGridLayout *mapLayout;
    QVBoxLayout *settingsLayout;
    QVBoxLayout *itemsLayout;

    //Widgets
    QEditorItemsWidget* qEditorItemsWidget;
    QEditorMapWidget* qMapEditorWidget;

    //Others
    CounterStrikeStyle styler;
    std::string selectedItem = "wall_1";
    std::string map_name = "map";
    YAML::Node map_config;

    // Methods
    void setupWidgets();

};

#endif // MAPEDITOR_H
