#ifndef PUZZLEWIDGET_H
#define PUZZLEWIDGET_H

#include <QPoint>
#include <QPixmap>
#include <QList>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;
QT_END_NAMESPACE

class PuzzleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PuzzleWidget(QWidget *parent = nullptr);
    void clear();

    int pieceSize() const;
    int imageSize() const;
    void addPiece(const QPixmap &pixmap, const QPoint &location);

signals:

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QGridLayout* layout;
};

#endif // PUZZLEWIDGET_H
