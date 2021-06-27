#include "MapEditor.h"
#include "ui_MapEditor.h"
#include <QDebug>

#define N 5

MapEditor::MapEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapEditor)
{

    styler.setCounterStrikeFont(this, 12);

    ui->setupUi(this);

    setupWidgets();

    setWindowTitle(tr("Counter Strike 2D - Map editor"));
}

MapEditor::~MapEditor()
{
    delete ui;
}

void MapEditor::handleSaveButton()
{
    this->close();
}

void MapEditor::handleQuitButton()
{
    this->close();
}

void MapEditor::loadMap(const std::string &name) {
    this->map_name = name;
}

void MapEditor::setupWidgets()
{
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
    qEditorItemsWidget = new QEditorItemsWidget(this);
    itemsLayout->addWidget(itemsLabel);
    itemsLayout->addWidget(qEditorItemsWidget);

    // map layout
    qMapEditorWidget = new QEditorMapWidget(this, 10, 10, this->map_name);
    mapLayout->addWidget(qMapEditorWidget);

    // connections
    connect(qEditorItemsWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this,SLOT(treeClicked(QTreeWidgetItem*,int)));

    // END
    this->setLayout(mainLayout);    

}

void MapEditor::treeClicked(QTreeWidgetItem* item, int column) {
    if(item->childCount() == 0) {
        std::string nameItem =item->text(0).toStdString();
        qMapEditorWidget->setItem(nameItem);
    }
}


