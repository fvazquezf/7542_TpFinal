#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QDialog>
#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QListView>
#include <QStringListModel>
#include <QGroupBox>

#include "yaml-cpp/yaml.h"
#include <fstream>
#include <list>

#include "QEditorItemsWidget.h"
#include "PiecesList.h"
#include "CounterStrikeStyle.h"
namespace Ui {
class MapEditor;
}

class MapEditor : public QDialog
{
    Q_OBJECT

public:
    explicit MapEditor(QWidget *parent = nullptr);
    void loadMap(const std::string &name);
    ~MapEditor();

private slots:
    void handleSaveButton();
    void handleQuitButton();
    void openImage();

private:
    Ui::MapEditor *ui;
    QListView* map;
    QListView* items;
    CounterStrikeStyle styler;

    void setupWidgets();

    std::string map_name = "map";
    YAML::Node map_config;

    PiecesList* piecesListMap;
    QGroupBox* gridGroupBox;

};

#endif // MAPEDITOR_H
