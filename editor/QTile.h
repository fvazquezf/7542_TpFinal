#ifndef QTILE_H
#define QTILE_H

#include <QLabel>
#include <QPixmap>
#include <QString>

class QTile : public QLabel
{
    Q_OBJECT    

    public:
        QTile (QWidget *parent, int width, int height, QPixmap &pixmap);

    private:
        void setEditorMapStyle(int width, int height);
};

#endif   //QTILE_H
