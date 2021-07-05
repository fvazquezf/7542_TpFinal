#include "MapCreationWindow.h"
#include "MapEditor.h"


#include "CounterStrikeStyle.h"
#include "paths.h"
MapCreationWindow::MapCreationWindow(QWidget *parent) :
    QDialog(parent)
{
    styler.setCounterStrikeFont(this, 14);
    this->setWindowTitle("Counter Strike 2D - Configuration");
    mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);
    this->setUpAll();
}

void MapCreationWindow::setUpAll(){

    saveButton = new QPushButton();
    mapNameEditLine = new QLineEdit();
    sizeComboBox = new QComboBox();

    saveButton->setText("Save");

    sizeComboBox->addItem("Small");
    sizeComboBox->addItem("Medium");
    sizeComboBox->addItem("Large");

    QLabel* titleMapName = new QLabel();
    QLabel* titleMapSize = new QLabel();
    QLabel* titleMain = new QLabel();

    titleMapName->setText("Map name");
    titleMapSize->setText("Map size");
    titleMain->setText("Map configuartion");

    QHBoxLayout* mapNameLayout = new QHBoxLayout();
    QHBoxLayout* mapSizeLayout = new QHBoxLayout();

    mapNameLayout->addWidget(titleMapName);
    mapNameLayout->addWidget(mapNameEditLine);
    mapSizeLayout->addWidget(titleMapSize);
    mapSizeLayout->addWidget(sizeComboBox);

    mainLayout->addWidget(titleMain);
    mainLayout->addLayout(mapNameLayout);
    mainLayout->addLayout(mapSizeLayout);
    mainLayout->addWidget(saveButton);

    connect(saveButton, SIGNAL(clicked()), this, SLOT(on_saveButton_clicked()));
}

MapCreationWindow::~MapCreationWindow()
{
}

void MapCreationWindow::on_saveButton_clicked()
{
    this->mapName = mapNameEditLine->text();
    this->mapSize = sizeComboBox->itemText(sizeComboBox->currentIndex());
    if(this->mapName == "") {
        QMessageBox::warning(this, tr("Map creation"),
                             tr("The map must have a name."),
                             QMessageBox::Close);
        return;
    }
    qDebug() << "Map name: " << this->mapName;
    qDebug() << "Map size: " << this->mapSize;

    this->close();
    MapEditor mapEditor(this, this->mapName.toStdString(), 15, 15);
    mapEditor.exec();
}
