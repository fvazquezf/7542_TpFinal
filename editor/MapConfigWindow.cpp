#include "MapConfigWindow.h"
#include "QEditorMapWidget.h"

MapConfigWindow::MapConfigWindow(QWidget *parent) :
    QDialog(parent)
{
    styler.setCounterStrikeFont(this, 14);
    this->setWindowTitle("Counter Strike 2D - Configuration");
    setMainLayout();
}

void MapConfigWindow::handleQuitPushButton()
{
    this->close();
}


void MapConfigWindow::handleCreatePushButton()
{
    this->execCreationWindow();
    this->qEditorMapList->update();
}

void MapConfigWindow::handleEditPushButton()
{
    if(this->selectedMap == "") {
        QMessageBox::warning(this, tr("Map editor"),
                        tr("Please select a map to edit."),
                        QMessageBox::Close);
        return;
    }
    this->close();
    MapEditor mapEditor(this, this->selectedMap.toStdString());
    mapEditor.exec();
    this->show();
}

void MapConfigWindow::handleClickMouse(QListWidgetItem* item) {
    this->selectedMap = item->text();
}

void MapConfigWindow::execCreationWindow() {
    this->close();
    MapCreationWindow mapCreationWindow;
    mapCreationWindow.setWindowTitle("Counter Strike 2D - Map editor");
    mapCreationWindow.exec();
    this->show();
}

void MapConfigWindow::setBottonLayout() {
    bottonLayout = new QHBoxLayout();

    QPushButton *editPushButton = new QPushButton("Edit", this);
    QPushButton *quitPushButton = new QPushButton("Quit", this);
    QPushButton *createPushButton = new QPushButton("Create", this);

    bottonLayout->addWidget(editPushButton,1);
    bottonLayout->addWidget(createPushButton,1);
    bottonLayout->addWidget(quitPushButton,1);

    connect(editPushButton, SIGNAL (released()), this, SLOT (handleEditPushButton()));
    connect(createPushButton, SIGNAL (released()), this, SLOT (handleCreatePushButton()));
    connect(quitPushButton, SIGNAL (released()), this, SLOT (handleQuitPushButton()));
}
void MapConfigWindow::setMainLayout() {
    setBottonLayout();
    mainLayout = new QVBoxLayout();
    qEditorMapList = new QEditorMapListWidget(this);

    connect(qEditorMapList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(handleClickMouse(QListWidgetItem*)));
    mainLayout->addWidget(qEditorMapList);
    mainLayout->addLayout(bottonLayout);
    this->setLayout(mainLayout);
}

MapConfigWindow::~MapConfigWindow() {
}


