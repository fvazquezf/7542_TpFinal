#include "MapEditor.h"
#include "ui_MapEditor.h"
#include <QFontDatabase>

MapEditor::MapEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapEditor)
{
    QFontDatabase::addApplicationFont("../../sprites/fonts/counter_strike.ttf");
    QFont CounterStrikeFont("Counter-Strike", 12, QFont::Normal);
    this->setFont(CounterStrikeFont);
    ui->setupUi(this);
}
QGridLayout* MapEditor::getLayout() {

    QGridLayout *mainLayout = new QGridLayout();
/*    QVBoxLayout *configLayout = new QVBoxLayout();
    QGridLayout *mapLayout = new QGridLayout();

    QLabel *label1 = new QLabel("config");
    QLabel *label2 = new QLabel("map");

    configLayout->addWidget(label1);

    mapLayout->addWidget(label2);

    mainLayout->addLayout(mapLayout, 0, 0);
    mainLayout->addLayout(configLayout, 0, 1);
*/
    return mainLayout;

}

MapEditor::~MapEditor()
{
    delete ui;
}

void MapEditor::on_pushButton_3_clicked()
{
    this->close();
}

void MapEditor::on_pushButton_2_clicked()
{
    this->close();
}
