#include "MapEditor.h"
#include "ui_MapEditor.h"
#include <QFontDatabase>
#include <QListWidget>

#include <QtWidgets>
#include <stdlib.h>
#include <vector>
#define N 5
#include "QEditorMapWidget.h"

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
    qDebug() <<"MAP EDITOR MAP" <<QString::fromStdString(name);

    this->map_name = name;
}

void MapEditor::openImage()
{
    const QString directory =
        QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).value(0, QDir::homePath());
    QFileDialog dialog(this, tr("Open Image"), directory);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    QStringList mimeTypeFilters;
    for (const QByteArray &mimeTypeName : QImageReader::supportedMimeTypes())
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");

}


void MapEditor::setupWidgets()
{
    QHBoxLayout *mainLayout = new QHBoxLayout();
    QGridLayout *mapLayout = new QGridLayout();
    QVBoxLayout *settingsLayout = new QVBoxLayout();
    QVBoxLayout *itemsLayout = new QVBoxLayout();

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
    QLabel *itemsLabel = new QLabel("Settings", this);/*
    QTreeWidget* qEditorItemsWidget = new QTreeWidget(this);
    qEditorItemsWidget->setColumnCount(2);
    QTreeWidgetItem* root = new QTreeWidgetItem();
    root->setText(0, QString::fromStdString("type"));
    root->setText(1, QString::fromStdString("icon)"));
    qEditorItemsWidget->addTopLevelItem(root);
    QTreeWidgetItem* child1 = new QTreeWidgetItem();
    child1->setText(1, "hola icon");
    child1->setText(0, "hola");
    root->addChild(child1);
    QTreeWidgetItem* child2 = new QTreeWidgetItem();
    child2->setText(0, "chau");
    child2->setText(1, "chau icon");
    root->addChild(child2);
    */
    QEditorItemsWidget* qEditorItemsWidget = new QEditorItemsWidget(this);
    itemsLayout->addWidget(itemsLabel);
    itemsLayout->addWidget(qEditorItemsWidget);

    // map layout
    QEditorMapWidget* qMapEditorWidget = new QEditorMapWidget(this, 10, 10, this->map_name);
    mapLayout->addWidget(qMapEditorWidget);

    // END
    this->setLayout(mainLayout);    

}

