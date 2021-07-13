#include "MapCreationWindow.h"

MapCreationWindow::MapCreationWindow(QWidget *parent) :
    QDialog(parent)
{
    styler.setCounterStrikeFont(this, 14);
    this->setWindowTitle("Counter Strike 2D - Configuration");
    mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);
    this->setUpAll();
}

void MapCreationWindow::setUpMapNameField() {

    QHBoxLayout* mapNameLayout = new QHBoxLayout();

    // Label
    QLabel* titleMapName = new QLabel();
    titleMapName->setText("Map name");
    mapNameLayout->addWidget(titleMapName);

    // LineEdit
    mapNameEditLine = new QLineEdit();
    mapNameLayout->addWidget(mapNameEditLine);

    mainLayout->addLayout(mapNameLayout);
}

void MapCreationWindow::setUpSizeField() {
    
    QHBoxLayout* mapSizeLayout = new QHBoxLayout();

    // Title
    QLabel* titleMapSize = new QLabel();
    titleMapSize->setText("Map size");

    mapSizeLayout->addWidget(titleMapSize);

    // ComboBox
    sizeComboBox = new QComboBox();

    sizeComboBox->addItem("Small");
    sizeComboBox->addItem("Medium");
    sizeComboBox->addItem("Large");

    mapSizeLayout->addWidget(sizeComboBox);

    mainLayout->addLayout(mapSizeLayout);
}

void MapCreationWindow::setUpSaveButton() {

    saveButton = new QPushButton();

    saveButton->setText("Save");

    connect(saveButton, SIGNAL(clicked()), this, SLOT(on_saveButton_clicked()));

    mainLayout->addWidget(saveButton);

}

void MapCreationWindow::setUpTitle() {

    QLabel* titleMain = new QLabel();

    titleMain->setText("Map configuartion");

    mainLayout->addWidget(titleMain);

}

void MapCreationWindow::setUpAll(){
    this->setUpTitle();
    this->setUpMapNameField();
    this->setUpSizeField();
    this->setUpSaveButton();
}

MapCreationWindow::~MapCreationWindow()
{
}

std::pair<int,int> MapCreationWindow::getSize() {
    if(this->mapSize == "Small") {
        return std::pair <int,int> (MAP_SIZE_SMALL_X,MAP_SIZE_SMALL_Y);
    } else if (this->mapSize == "Medium") {
        return std::pair <int,int> (MAP_SIZE_MEDIUM_X,MAP_SIZE_MEDIUM_Y);
    } else {
        return std::pair <int,int> (MAP_SIZE_LARGE_X,MAP_SIZE_LARGE_Y);
    }
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

    this->close();
    std::pair<int,int> size = this->getSize();
    MapEditor mapEditor(this, this->mapName.toStdString(), size.first, size.second);
    mapEditor.exec();
}
