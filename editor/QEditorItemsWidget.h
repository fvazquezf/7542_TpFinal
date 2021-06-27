#ifndef QEDITOR_ITEMS_WIDGET_H
#define QEDITOR_ITEMS_WIDGET_H
#include <vector>
#include <QTreeWidget>
#include <QWidget>
#include <QIcon>
#include "MapIconGenerator.h"

class QEditorItemsWidget : public QTreeWidget {
    Q_OBJECT

public:

    QEditorItemsWidget(QWidget* parent);

private:
    MapIconGenerator icons;
    void setMapItems();
};

#endif   //QEDITOR_ITEMS_WIDGET_H

