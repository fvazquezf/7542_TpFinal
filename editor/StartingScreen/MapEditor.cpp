#include "MapEditor.h"
#include "ui_MapEditor.h"
#include <QFontDatabase>
#include <QListWidget>

#include <QtWidgets>
#include <stdlib.h>
#include <vector>

MapEditor::MapEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MapEditor)
{

    QFontDatabase::addApplicationFont("../../sprites/fonts/counter_strike.ttf");
    QFont CounterStrikeFont("Counter-Strike", 12, QFont::Normal);
    this->setFont(CounterStrikeFont);
    ui->setupUi(this);

    setupMenus();
    setupWidgets();

    setWindowTitle(tr("Counter Strike 2D - Map editor"));

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

void MapEditor::loadMap(const std::string &path)
{
    YAML::Node config;
    try{
        map_config = YAML::LoadFile(path);}
    catch (YAML::BadFile ex) {
        std::ofstream createFile { path };
        map_config = YAML::LoadFile(path);
    }
    map_config["prueba"] = "Maria";
    QString username;
    username = QString(map_config["prueba"].as<std::string>().c_str());
    qDebug() << "Map size: " << username;

    setupPuzzle();
}

void MapEditor::setCompleted()
{
    QMessageBox::information(this, tr("Puzzle Completed"),
                             tr("Congratulations! You have completed the puzzle!\n"
                                "Click OK to start again."),
                             QMessageBox::Ok);

    setupPuzzle();
}

void MapEditor::setupPuzzle()
{
    QString fileName = QStringLiteral(":/sprites/img/wall.png");

    QPixmap newImage;
    newImage.load(fileName);
    puzzleImage = newImage;
    int size = qMin(puzzleImage.width(), puzzleImage.height());
    puzzleImage = puzzleImage.copy((puzzleImage.width() - size) / 2,
        (puzzleImage.height() - size) / 2, size, size).scaled(puzzleWidget->width(),
            puzzleWidget->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    piecesList->clear();

    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; ++x) {
            int pieceSize = puzzleWidget->pieceSize();
            QPixmap pieceImage = puzzleImage.copy(x * pieceSize, y * pieceSize, pieceSize, pieceSize);
            piecesList->addPiece(pieceImage, QPoint(x, y));
        }
    }
    std::vector<std::vector<int>> elementos = map_config["wall"].as<std::vector<std::vector<int>>>();
    qDebug() << QString::number(elementos[0][0]) ;
    for (unsigned long i = 0; i< elementos.size(); i ++) {
        this->puzzleWidget->addPiece(newImage, QPoint(elementos[i][0], elementos[i][1]));
    }

    puzzleWidget->clear();
}

void MapEditor::setupMenus()
{

}

void MapEditor::setupWidgets()
{
    QHBoxLayout *frameLayout = new QHBoxLayout();
    puzzleWidget = new PuzzleWidget(400);

    piecesList = new PiecesList(puzzleWidget->pieceSize(), this);


    connect(puzzleWidget, &PuzzleWidget::puzzleCompleted,
            this, &MapEditor::setCompleted, Qt::QueuedConnection);

    frameLayout->addWidget(piecesList);
    frameLayout->addWidget(puzzleWidget);
    this->setLayout(frameLayout);
}

