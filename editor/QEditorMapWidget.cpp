#include "QEditorMapWidget.h"
#include <QtDebug>
#include <exception>
#include <QScrollArea>
#include <QTabWidget>
#include <QDrag>
#include <QWindow>
#include <QMimeData>
#include <QByteArrayList>
#include <QRegularExpression>

#include <QPixmap>

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
    QPixmap backgorundIcon = pixmaps.getPixmap(this->selectedBackground);
    QTile* backgorundIconQTile = new QTile(this, QTILE_SIZE, QTILE_SIZE, backgorundIcon);
    layout->addWidget(backgorundIconQTile, row, column);
    if(elements.size() == 0) {
        return;
    }
    QPixmap icon = pixmaps.getPixmap(element);
    QTile* tile = new QTile(this, QTILE_SIZE, QTILE_SIZE, icon);
    positions[std::pair<int,int>(row, column)] = element;
    layout->addWidget(tile, row, column);
}

void QEditorMapWidget::loadNewFile(int rows, int columns) {
    size[LABEL_COLUMNS] = columns;
    size[LABEL_ROWS] = rows;
    this->setTilesFromNewFile();

}

void QEditorMapWidget::updateBackGround() {

    QPixmap backgroundQPixmap = pixmaps.getPixmap(selectedBackground);
    for (int i = 0; i < layout->count(); ++i) {
        QTile *widget = (QTile*) layout->itemAt(i)->widget();
        widget->setPixmap(backgroundQPixmap);
    }

    std::map <std::pair<int,int>, std::string>::iterator it;
    for (it = positions.begin(); it != positions.end(); ++it) {
            QPixmap pixmap = pixmaps.getPixmap(it->second);
            QTile* tile = new QTile(this, QTILE_SIZE, QTILE_SIZE, pixmap);
            int x = it->first.first;
            int y = it->first.second;
            layout->addWidget(tile, x, y);
    }


}

void QEditorMapWidget::setTilesBackGround() {
    QPixmap backgroundQPixmap = pixmaps.getPixmap(selectedBackground);
    for (int i = 0; i < size[LABEL_ROWS]; ++i) {
        for (int j = 0; j < size[LABEL_COLUMNS]; ++j) {
            QTile* tile = new QTile(this, QTILE_SIZE, QTILE_SIZE, backgroundQPixmap);
            layout->addWidget(tile, i, j);
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

    this->size[LABEL_COLUMNS] = map_config[LABEL_COLUMNS].as<int>();
    this->size[LABEL_ROWS] = map_config[LABEL_ROWS].as<int>();
    this->selectedBackground = map_config[LABEL_BACKGROUND].as<std::string>();

    this->setTilesBackGround();

    for (unsigned long i = 0; i< elements.size(); i ++) {
        if(map_config[elements[i]]) {
            std::list<std::list<int>> pos = map_config[elements[i]].as<std::list<std::list<int>>>();
            std::list<std::list<int>> ::iterator it;
            for (it = pos.begin(); it != pos.end(); ++it) {
                std::list<int> ::iterator it2 = (*it).begin();
                int x = *(it2);
                int y = *(++it2);
                positions[std::pair<int,int>(x, y)] = elements[i];
                this->addQTile(elements[i], x, y);
            }
        }
    }
}

void QEditorMapWidget::updateMapLFile() {
    std::string path = PATH_TO_MAPS + map_name + ".yml";
    std::ofstream outfile;
    outfile.open(path);

    YAML::Emitter out;
    out << size;
    
    std::map<std::string, std::list<std::pair<int,int>>> tiles;

    std::map <std::pair<int,int>, std::string>::iterator it;
    for (it = positions.begin(); it != positions.end(); ++it) {
        tiles[it->second].push_back(it->first);
    }

    std::string res = LABEL_BACKGROUND;
    res += ": " + selectedBackground + "\n";
    for (unsigned long i = 0; i < elements.size(); i ++) {
        if(tiles[elements[i]].size() == 0) {
            continue;
        }
        res += elements[i] + ":\n";
        std::list<std::pair<int,int>> ::iterator it;
        for (it = tiles[elements[i]].begin(); it != tiles[elements[i]].end(); ++it) {
            res += "  - [" + std::to_string(it->first) + "," + std::to_string(it->second) + "]\n";
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
        updateBackGround();
    }
}

void QEditorMapWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->source() == this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->acceptProposedAction();
    }
}

void QEditorMapWidget::dropEvent(QDropEvent *event)
{   
    event->setDropAction(Qt::MoveAction);
    event->accept();
    
    const QMimeData *mime = event->mimeData();

    QPoint position = event->pos();

    QPoint hotSpot;
    QByteArrayList hotSpotPos = mime->data("application/x-hotspot").split(' ');
    hotSpot.setX(hotSpotPos.first().toInt());
    hotSpot.setY(hotSpotPos.last().toInt());

    std::pair<int,int> pos1(position.y()/QTILE_SIZE, position.x()/QTILE_SIZE);
    std::pair<int,int> pos2(hotSpot.y()/QTILE_SIZE, hotSpot.x()/QTILE_SIZE);

    if(pos1 == pos2) {
        // Point and click
        QPoint pos = event->pos();
        int row = pos.y() / QTILE_SIZE;
        int column = pos.x() / QTILE_SIZE;
        this->addQTile(this->selectedItem, row, column);
        return;
    } else {
        // Drag and drop
        std::string aux = positions[pos1];
        positions[pos1] = positions[pos2];
        positions[pos2] = aux;
        this->addQTile(positions[pos1], pos1.first, pos1.second);
        this->addQTile(positions[pos2], pos2.first, pos2.second);
    }

}

void QEditorMapWidget::mousePressEvent(QMouseEvent *event) {

    // Drag and Drop
    QLabel *child = qobject_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPoint pos = event->pos();
    QPoint hotSpot = event->pos() - child->pos();
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-hotspot",
                      QByteArray::number(pos.x()) + ' ' + QByteArray::number(pos.y()));

    qreal dpr = window()->windowHandle()->devicePixelRatio();
    QPixmap pixmap(child->size() * dpr);
    pixmap.setDevicePixelRatio(dpr);
    child->render(&pixmap);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(hotSpot);
    drag->exec(Qt::MoveAction);
}
