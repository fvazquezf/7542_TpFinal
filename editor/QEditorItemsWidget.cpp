#include "QEditorItemsWidget.h"
#include <QtDebug>

#define HEADER_LABEL "Map elements"

QEditorItemsWidget::QEditorItemsWidget(QWidget* parent):
    QTreeWidget (parent) {
    this->setHeaderLabel(HEADER_LABEL);
    this->setMapItems();
}

void QEditorItemsWidget::setMapItems() {
    std::vector<std::string> types = icons.getTypes();
    for(unsigned long i = 0; i < types.size(); i++) {
        QTreeWidgetItem* root = new QTreeWidgetItem();
        root->setText(0, QString::fromStdString(types[i]));
        this->addTopLevelItem(root);
        std::list<std::string> names = icons.getIconsNames(types[i]);
        std::list<std::string>::iterator it;
        for(it = names.begin(); it != names.end(); it++) {
            QTreeWidgetItem* child = new QTreeWidgetItem();
            child->setText(0, QString::fromStdString(*it));
            child->setIcon(0, icons.getIcon(*it));
            root->addChild(child);
        }
    }
}
