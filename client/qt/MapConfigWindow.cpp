#include "MapConfigWindow.h"

MapConfigWindow::MapConfigWindow(QWidget *parent, int width, int height, LogInInfo &info)
    : QDialog(parent), width(width), height(height), info(&info)
{

    styler.setCounterStrikeFont(this, 14);
    this->setWindowTitle("Counter Strike 2D - Configuration");
    setMainLayout();
}

void MapConfigWindow::handleJoinPushButton()
{
    info->map = this->selectedMap.toStdString();
    this->close();
}



void MapConfigWindow::handleClickMouse(QListWidgetItem* item) {
    this->selectedMap = item->text();
}


void MapConfigWindow::setBottonLayout() {
    bottonLayout = new QHBoxLayout();

    QPushButton *joinPushButton = new QPushButton("Join", this);

    bottonLayout->addWidget(joinPushButton,1);

    connect(joinPushButton, SIGNAL (released()), this, SLOT (handleJoinPushButton()));
}
void MapConfigWindow::setMainLayout() {
    setBottonLayout();
    mainLayout = new QVBoxLayout();
    qEditorMapList = new QEditorMapListWidget(nullptr, width, height, *info);

    connect(qEditorMapList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(handleClickMouse(QListWidgetItem*)));
    mainLayout->addWidget(qEditorMapList);
    mainLayout->addLayout(bottonLayout);
    this->setLayout(mainLayout);
}

MapConfigWindow::~MapConfigWindow() {
}


