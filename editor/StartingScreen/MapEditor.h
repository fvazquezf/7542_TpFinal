#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <QDialog>
#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QListView>
#include <QStringListModel>

#include "yaml-cpp/yaml.h"
#include <fstream>

#include "PiecesList.h"
#include "PuzzleWidget.h"

namespace Ui {
class MapEditor;
}

class MapEditor : public QDialog
{
    Q_OBJECT

public:
    explicit MapEditor(QWidget *parent = nullptr);
    void loadMap(const std::string &path);
    ~MapEditor();

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void openImage();
    void setupPuzzle();

private:
    Ui::MapEditor *ui;
    QListView* map;
    QListView* items;
    void setupMenus();
    void setupWidgets();
    void setCompleted();

    YAML::Node map_config;
    QPixmap puzzleImage;
    PiecesList *piecesList;
    PuzzleWidget *puzzleWidget;
};

#endif // MAPEDITOR_H
