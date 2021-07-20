#include "MapEditor.h"

MapEditor::MapEditor(QWidget *parent, const std::string &name) :
    QDialog(parent)
{
    this->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    styler.setCounterStrikeFont(this, 16);
    this->map_name = name;
    this->qMapEditorWidget = new QEditorMapWidget(this, this->map_name);
    setupWidgets();
    setWindowTitle(tr("Counter Strike 2D - Map editor"));
}


MapEditor::MapEditor(QWidget *parent, const std::string &name, int row, int column) :
    QDialog(parent)
{
    this->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
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
    if(qMapEditorWidget->hasValidZones()) {
        qMapEditorWidget->updateMapLFile();
        this->close();
        return;
    }
    QMessageBox::warning(this, tr("Map editor"),
                        tr("Valid zones not set. They have to be rectangular."),
                        QMessageBox::Close);
}

void MapEditor::handleQuitButton()
{
    this->close();
}

void MapEditor::setupWidgets()
{
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(false);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidget(qMapEditorWidget);

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
    qEditorItemsWidget = new QEditorItemsWidget(nullptr);
    itemsLayout->addWidget(itemsLabel);
    itemsLayout->addWidget(qEditorItemsWidget);

    // map layout
    mapLayout->addWidget(scrollArea);

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


