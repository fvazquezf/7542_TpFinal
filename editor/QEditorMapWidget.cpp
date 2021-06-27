#include "QEditorMapWidget.h"
#define QTILE_SIZE 32
#define PATH_TO_MAPS "../maps/"
#include <QtDebug>
#include <exception>
#include<QScrollArea>

QEditorMapWidget::QEditorMapWidget (QWidget* parent, int rows, int columns, std::string &map_name) :
        QWidget (parent), rows(rows), columns(columns), map_name(map_name) {
        this->setAcceptDrops(true);
        this->setMapLayout();
        this->setEmptyMap();
        this->setTileFromFile();
}

void QEditorMapWidget::setMapLayout() {
    layout = new QGridLayout (this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    this->setLayout(layout);
}

void QEditorMapWidget::setEmptyMap() {
    for(int i = 0; i<rows; i++){
        for(int j = 0; j<columns; j++){
            std::string s = "aztec";
            this->addQTile(s, i, j);
        }
    }
}

void QEditorMapWidget::loadFile() {
    std::string path = PATH_TO_MAPS + map_name + ".yml";
    std::ofstream outfile;
    outfile.open(path, std::ios_base::app);
    outfile << "size:\n  - height: 200\n  - width: 320\nbackgound: \"\"\nelements: []";
    outfile.close();
    map_config = YAML::LoadFile(path);
}

void QEditorMapWidget::updateFile() {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; i < columns; j++) {
            // TO-DO
        }
    }
}

void QEditorMapWidget::addQTile(std::string &element, int row, int column) {
    QIcon icon = icons.getIcon(element);
    QTile* tile = new QTile(this, QTILE_SIZE, QTILE_SIZE, icon);
    //tiles[column][row] = element;
    layout->addWidget(tile, row, column);
}

void QEditorMapWidget::setTileFromFile(std::string &element) {
    std::vector<std::vector<int>> pos = map_config[element].as<std::vector<std::vector<int>>>();
    for (unsigned long i = 0; i< pos.size(); i ++) {
        this->addQTile(element, pos[i][0], pos[i][1]);
    }
}

void QEditorMapWidget::setTileFromFile() {

    this->loadFile();
    std::vector<std::string> elements = map_config["elements"].as<std::vector<std::string>>();
    for (unsigned long i = 0; i< elements.size(); i ++) {
        this->setTileFromFile(elements[i]);
    }
}

void QEditorMapWidget::setItem(std::string &item) {
    this->selectedItem = item;
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
