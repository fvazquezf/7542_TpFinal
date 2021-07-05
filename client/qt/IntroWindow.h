#ifndef INTROWINDOW_H
#define INTROWINDOW_H

#include <QDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QUrl>

class IntroWindow : public QVideoWidget
{
    Q_OBJECT
    public:
        IntroWindow(QWidget *parent, int width, int heigth);
        void run();
        ~IntroWindow() override;
   private:
        QMediaPlaylist* playlist;
        QMediaPlayer* player;
};

#endif // INTROWINDOW_H
