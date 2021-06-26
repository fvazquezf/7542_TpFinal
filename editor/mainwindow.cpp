#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./MapEditor.h"
#include "./MapCreationWindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Q_INIT_RESOURCE(resource);
    styler.setCounterStrikeFont(this, 12);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_createButton_clicked()
{
    this->execCreationWindow();
}

void MainWindow::on_editButton_clicked()
{
    QString mapName = "nombre mapa";
    this->execEditorWindow(mapName);
}

void MainWindow::execCreationWindow() {
    this->close();
    MapCreationWindow mapCreationWindow;
    mapCreationWindow.setWindowTitle("Counter Strike 2D - Map editor");
    mapCreationWindow.exec();
    this->show();
}

void MainWindow::execEditorWindow(QString &mapName) {
    this->close();
    MapEditor mapEditor;
    mapEditor.loadMap(mapName.toStdString());
    mapEditor.show();
    mapEditor.exec();
    this->show();
}
