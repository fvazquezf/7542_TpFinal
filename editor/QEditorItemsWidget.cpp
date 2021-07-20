#include "QEditorItemsWidget.h"

#define HEADER_LABEL "Map elements"

QEditorItemsWidget::QEditorItemsWidget(QWidget* parent):
    QTreeWidget (parent) {
    this->setHeaderLabel(HEADER_LABEL);
    this->setMapItems();
}

void QEditorItemsWidget::setMapItems() {
    MapQPixmapGenerator pixmaps;    
    std::vector<std::string> types = pixmaps.getTypes();
    for(unsigned long i = 0; i < types.size(); i++) {
        QTreeWidgetItem* root = new QTreeWidgetItem();
        root->setText(0, QString::fromStdString(types[i]));
        this->addTopLevelItem(root);
        std::list<std::string> names = pixmaps.getPixmapsNames(types[i]);
        std::list<std::string>::iterator it;
        for(it = names.begin(); it != names.end(); it++) {
            QTreeWidgetItem* child = new QTreeWidgetItem();
            child->setText(0, QString::fromStdString(*it));
            child->setIcon(0, QIcon(pixmaps.getPixmap(*it)));
            root->addChild(child);
        }
    }
}
