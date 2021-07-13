#ifndef QEDITOR_ITEMS_WIDGET_H
#define QEDITOR_ITEMS_WIDGET_H
#include <vector>
#include <QTreeWidget>
#include <QWidget>
#include <QIcon>
#include "MapQPixmapGenerator.h"
#include <QMouseEvent>

class QEditorItemsWidget : public QTreeWidget {
    Q_OBJECT

public:
    QEditorItemsWidget(QWidget* parent);
private:
    MapQPixmapGenerator pixmaps;
    void setMapItems();
    std::string selectedItem;
    std::vector<std::string> types;
    void handleClickedLabel();

};

#endif   //QEDITOR_ITEMS_WIDGET_H

