#include "MapConfigWindow.h"
#include "ui_MapConfigWindow.h"

MapConfigWindow::MapConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapConfigWindow)
{
    ui->setupUi(this);
    styler.setCounterStrikeFont(this, 14);
    setMainLayout();
}

MapConfigWindow::~MapConfigWindow()
{
    delete ui;
}


void MapConfigWindow::handleJoinPushButton()
{
}


void MapConfigWindow::handleCreatePushButton()
{
    this->execCreationWindow();
    this->qEditorMapList->update();
}

void MapConfigWindow::handleEditPushButton()
{
    this->execEditorWindow(this->selectedMap);
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

void MapConfigWindow::execEditorWindow(QString &mapName) {
    this->close();
    MapEditor mapEditor(this, mapName.toStdString());
    mapEditor.exec();
    this->show();
}

void MapConfigWindow::setBottonLayout() {
    bottonLayout = new QHBoxLayout();

    QPushButton *editPushButton = new QPushButton("Edit", this);
    QPushButton *joinPushButton = new QPushButton("Join", this);
    QPushButton *createPushButton = new QPushButton("Create", this);

    bottonLayout->addWidget(editPushButton,1);
    bottonLayout->addWidget(createPushButton,1);
    bottonLayout->addWidget(joinPushButton,1);

    connect(editPushButton, SIGNAL (released()), this, SLOT (handleEditPushButton()));
    connect(createPushButton, SIGNAL (released()), this, SLOT (handleCreatePushButton()));
    connect(joinPushButton, SIGNAL (released()), this, SLOT (handleJoinPushButton()));
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

