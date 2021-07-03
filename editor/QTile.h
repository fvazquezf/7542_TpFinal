#ifndef QTILE_H
#define QTILE_H

#include <QLabel>
#include <QIcon>

class QTile : public QLabel
{
    Q_OBJECT    

    public:
        QTile (QWidget *parent, int width, int height, QIcon &icon);

    private:
        QIcon icon;
        void setEditorMapStyle(int width, int height);
};

#endif   //QTILE_H
