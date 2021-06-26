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
    QLabel *itemsLabel = new QLabel("Settings", this);
    itemsLayout->addWidget(itemsLabel);

    // map layout
    QEditorMapWidget* qMapEditorWidget = new QEditorMapWidget(this, 10, 10, this->map_name);
    mapLayout->addWidget(qMapEditorWidget);

    // END
    this->setLayout(mainLayout);    

}

