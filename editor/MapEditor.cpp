#include "MapEditor.h"
#include <QDebug>

#define N 5
#define TILE_SIZE 32
#define PATH_TO_MAPS "../maps/"
#define WIDTH 15
#define HEIGHT 15

MapEditor::MapEditor(QWidget *parent, const std::string &name) :
    QDialog(parent)
{
    styler.setCounterStrikeFont(this, 12);
    this->map_name = name;
    this->qMapEditorWidget = new QEditorMapWidget(this, this->map_name);
    setupWidgets();
    setWindowTitle(tr("Counter Strike 2D - Map editor"));
}


MapEditor::MapEditor(QWidget *parent, const std::string &name, int row, int column) :
    QDialog(parent)
{
    styler.setCounterStrikeFont(this, 12);
    this->map_name = name;
    this->qMapEditorWidget = new QEditorMapWidget(this, this->map_name, row, column);
    setupWidgets();
    setWindowTitle(tr("Counter Strike 2D - Map editor"));
}

MapEditor::~MapEditor()
{
}

void MapEditor::handleSaveButton()
{
    qMapEditorWidget->updateMapLFile();
    this->close();
}

void MapEditor::handleQuitButton()
{
    this->close();
}

void MapEditor::setupWidgets()
{

    QScrollArea *posts = new QScrollArea();
    posts->setWidgetResizable(false);
    posts->setFrameShape(QFrame::NoFrame);

    mainLayout = new QHBoxLayout();
    mapLayout = new QGridLayout();
    settingsLayout = new QVBoxLayout();
    itemsLayout = new QVBoxLayout();

    // main layout
    mainLayout->addLayout(mapLayout);
    mainLayout->addLayout(settingsLayout);

    // settings layout:
    settingsLayout->addLayout(itemsLayout, 0);

    QPushButton *savePushButton = new QPushButton("Save", this);
    QPushButton *quitPushButton = new QPushButton("Quit", this);

    settingsLayout->addWidget(savePushButton,2);
    settingsLayout->addWidget(quitPushButton,1);

    connect(savePushButton, SIGNAL (released()), this, SLOT (handleSaveButton()));
    connect(quitPushButton, SIGNAL (released()), this, SLOT (handleQuitButton()));

    // items layout
    QLabel *itemsLabel = new QLabel("Settings", this);
    qEditorItemsWidget = new QEditorItemsWidget(posts);
    itemsLayout->addWidget(itemsLabel);
    itemsLayout->addWidget(posts);

    // map layout
    mapLayout->addWidget(qMapEditorWidget);

    // connections
    connect(qEditorItemsWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(treeClicked(QTreeWidgetItem*,int)));

    // END
    this->setLayout(mainLayout);    

}

void MapEditor::treeClicked(QTreeWidgetItem* item, int column) {
    if(item->childCount() == 0) {
        std::string nameItem =item->text(0).toStdString();
        qMapEditorWidget->setItem(nameItem);
    }
}


