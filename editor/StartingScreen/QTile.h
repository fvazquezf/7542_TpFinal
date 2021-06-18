#ifndef QTILE_H
#define QTILE_H

#include <QWidget>

namespace Ui {
class QTile;
}

class QTile : public QWidget
{
    Q_OBJECT

public:
    explicit QTile(QWidget *parent = nullptr);
    ~QTile();

private:
    Ui::QTile *ui;
};

#endif // QTILE_H
