#ifndef COUNTERSTRIKESTYLE_H
#define COUNTERSTRIKESTYLE_H

#include <QDialog>

class CounterStrikeStyle
{
public:
    CounterStrikeStyle();
    void setCounterStrikeFont(QDialog* qDialog, int size);
    void setCounterStrikeFont(QWidget* qWidget, int size);

};

#endif // COUNTERSTRIKESTYLE_H
