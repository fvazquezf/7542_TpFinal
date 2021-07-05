#include "QEditorMapWidget.h"
#define QTILE_SIZE 32
#include "paths.h"
#include <QtDebug>
#include <exception>
#include<QScrollArea>

#define ROWS "size_rows"
#define COLUMNS "size_columns"
#define BACKGROUND "background"

QEditorMapWidget::QEditorMapWidget (QWidget* parent, std::string &map_name, int rows, int columns) :
        QWidget (parent), map_name(map_name) {
    this->setAcceptDrops(true);
    this->setMapLayout();
    this->loadNewFile(rows, columns);
}

QEditorMapWidget::QEditorMapWidget (QWidget* parent, std::string &map_name) :
        QWidget (parent), map_name(map_name) {
    this->setAcceptDrops(true);
    this->setMapLayout();
    this->loadOldFile();
}

void QEditorMapWidget::setMapLayout() {
    layout = new QGridLayout (this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    this->setLayout(layout);
}

void QEditorMapWidget::addQTile(std::string &element, int row, int column) {
    QIcon icon = icons.getIcon(element);
    QTile* tile = new QTile(this, QTILE_SIZE, QTILE_SIZE, icon);
    std::list<int> pos = {row, column};
    tiles[element].push_back(pos);
    layout->addWidget(tile, row, column);
}

void QEditorMapWidget::loadNewFile(int rows, int columns) {
    size[COLUMNS] = columns;
    size[ROWS] = rows;
    this->setTilesFromNewFile();

}

void QEditorMapWidget::setTilesBackGround() {
    for(int i = 0; i<  size[ROWS]; i++){
        for(int j = 0; j < size[COLUMNS]; j++){
            QIcon icon = icons.getIcon(selectedBackground);
            QTile* tile = new QTile(this, QTILE_SIZE, QTILE_SIZE, icon);
            layout->addWidget(tile, i, j);
        }
    }

    for (unsigned long i = 0; i < elements.size(); i ++) {
        if(tiles[elements[i]].size() == 0) {
            continue;
        }
        std::list<std::list<int>> ::iterator it;
        for (it = tiles[elements[i]].begin(); it != tiles[elements[i]].end(); ++it) {
            std::list<int> ::iterator it2 = (*it).begin();
            QIcon icon = icons.getIcon(elements[i]);
            QTile* tile = new QTile(this, QTILE_SIZE, QTILE_SIZE, icon);
            int x = *(it2);
            int y = *(++it2);
            layout->addWidget(tile, x, y);
        }
    }
}

void QEditorMapWidget::setTilesFromNewFile() {
    this->setTilesBackGround();
}

void QEditorMapWidget::loadOldFile() {
    this->setTilesFromOldFile();
}

void QEditorMapWidget::setTilesFromOldFile() {

    std::string path = PATH_TO_MAPS + map_name + ".yml";
    YAML::Node map_config = YAML::LoadFile(path);

    this->size[COLUMNS] = map_config[COLUMNS].as<int>();
    this->size[ROWS] = map_config[ROWS].as<int>();
    this->selectedBackground = map_config[BACKGROUND].as<std::string>();

    this->setTilesBackGround();

    for (unsigned long i = 0; i< elements.size(); i ++) {
        try {
            std::list<std::list<int>> pos = map_config[elements[i]].as<std::list<std::list<int>>>();
            std::list<std::list<int>> ::iterator it;
            for (it = pos.begin(); it != pos.end(); ++it) {
                std::list<int> ::iterator it2 = (*it).begin();
                this->addQTile(elements[i], *(it2), *(it2++));
            }
        } catch(YAML::BadConversion ex) {

        }
    }
}

void QEditorMapWidget::updateMapLFile() {
    std::string path = PATH_TO_MAPS + map_name + ".yml";
    std::ofstream outfile;
    outfile.open(path);

    YAML::Emitter out;
    out << size;
    

    std::string res = BACKGROUND;
    res += ": " + selectedBackground + "\n";
    for (unsigned long i = 0; i < elements.size(); i ++) {
        if(tiles[elements[i]].size() == 0) {
            continue;
        }
        res += elements[i] + ":\n";
        std::list<std::list<int>> ::iterator it;
        for (it = tiles[elements[i]].begin(); it != tiles[elements[i]].end(); ++it) {
            std::list<int> ::iterator it2 = (*it).begin();
            res += "  - [" + std::to_string(*(it2)) + "," + std::to_string(*(it2++)) + "]\n";
        }
        res += "\n";
    }

    outfile << out.c_str();
    outfile << "\n" << res;
    outfile.close();
}

void QEditorMapWidget::setItem(std::string &item) {
    if(std::count(elements.begin(), elements.end(), item)){
        this->selectedItem = item;
    } else {
        this->selectedBackground = item;
        setTilesBackGround();
    }
}

/*
void QEditorMapWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat(fridgetMagnetsMimeType())) {
        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();

    } else if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void QEditorMapWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat(fridgetMagnetsMimeType())) {
        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void QEditorMapWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat(fridgetMagnetsMimeType())) {
        const QMimeData *mime = event->mimeData();
        QByteArray itemData = mime->data(fridgetMagnetsMimeType());
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString text;
        QPoint offset;
        dataStream >> text >> offset;

        DragLabel *newLabel = new DragLabel(text, this);
        newLabel->move(event->pos() - offset);
        newLabel->show();
        newLabel->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else if (event->mimeData()->hasText()) {
        QStringList pieces = event->mimeData()->text().split(
            QRegularExpression(QStringLiteral("\\s+")), Qt::SkipEmptyParts);
        QPoint position = event->pos();

        for (const QString &piece : pieces) {
            DragLabel *newLabel = new DragLabel(piece, this);
            newLabel->move(position);
            newLabel->show();
            newLabel->setAttribute(Qt::WA_DeleteOnClose);

            position += QPoint(newLabel->width(), 0);
        }

        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}
*/
void QEditorMapWidget::mousePressEvent(QMouseEvent *event) {
    if(event->type() == QMouseEvent::MouseButtonPress) {
        QPoint pos = event->pos();
        int row = pos.y() / QTILE_SIZE;
        int column = pos.x() / QTILE_SIZE;
        this->addQTile(this->selectedItem, row, column);
    }
/*
    DragLabel *child = static_cast<DragLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPoint hotSpot = event->pos() - child->pos();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << child->labelText() << QPoint(hotSpot);

    QMimeData *mimeData = new QMimeData;
    mimeData->setData(fridgetMagnetsMimeType(), itemData);
    mimeData->setText(child->labelText());

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(child->pixmap(Qt::ReturnByValue));
    drag->setHotSpot(hotSpot);

    child->hide();

    if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
        child->close();
    else
        child->show();
        */
}
