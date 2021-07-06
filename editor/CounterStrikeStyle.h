#ifndef COUNTERSTRIKESTYLE_H
#define COUNTERSTRIKESTYLE_H

#include <QDialog>
#include <QString>

#include "constantes.h"

class CounterStrikeStyle
{
public:
    CounterStrikeStyle();
    void setCounterStrikeFont(QDialog* qDialog, int size);
    void setCounterStrikeFont(QWidget* qWidget, int size);
private:
    QString font_path;
};

#endif // COUNTERSTRIKESTYLE_H
