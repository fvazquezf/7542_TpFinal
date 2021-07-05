#include <QLabel>
#include "MapConfigWindow.h"
#include <QMessageBox>
MapConfigWindow::MapConfigWindow(QWidget *parent, int width, int height, LogInInfo &info, bool create)
    : QDialog(parent),
      width(width),
      height(height),
      info(info),
      createWindow(create),
      usernameLineEdit(nullptr){
    styler.setCounterStrikeFont(this, 14);
    this->setWindowTitle("Counter Strike 2D - Configuration");
    setMainLayout();
    if (create){
        this->setEditLinesLayout();
    }
}

void MapConfigWindow::handleJoinPushButton() {
    if (this->selectedMap == "")
        QMessageBox::warning(this, tr("Log In error"),
                             tr("Username field is empty."),
                             QMessageBox::Close);
    return;
    info.map = this->selectedMap.toStdString();
    this->close();
}

void MapConfigWindow::handleClickMouse(QListWidgetItem* item) {
    this->selectedMap = item->text();
}

void MapConfigWindow::setEditLinesLayout() {
    QHBoxLayout *usernameLayout = new QHBoxLayout();

    QLabel *userLabel = new QLabel();
    userLabel->setText("GAME NAME");

    usernameLineEdit = new QLineEdit();

    usernameLayout->addWidget(userLabel);

    usernameLayout->addWidget(usernameLineEdit);

    mainLayout->addLayout(usernameLayout);
}


void MapConfigWindow::setBottonLayout() {
    bottonLayout = new QHBoxLayout();

    QPushButton *joinPushButton = new QPushButton(createWindow ? "Create" : "Join", this);

    bottonLayout->addWidget(joinPushButton,1);

    connect(joinPushButton, SIGNAL (released()), this, SLOT (handleJoinPushButton()));
}

void MapConfigWindow::setMainLayout() {
    setBottonLayout();
    mainLayout = new QVBoxLayout();
    qEditorMapList = new QEditorMapListWidget(nullptr, width, height, info);

    connect(qEditorMapList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(handleClickMouse(QListWidgetItem*)));
    mainLayout->addWidget(qEditorMapList);
    mainLayout->addLayout(bottonLayout);
    this->setLayout(mainLayout);
}

MapConfigWindow::~MapConfigWindow() {
}


