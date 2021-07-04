#include "CounterStrikeStyle.h"
#include <QFontDatabase>

#define PATH_TO_COUNTER_STRIKE_FONT ":/resources/fonts/counter_strike.ttf"
CounterStrikeStyle::CounterStrikeStyle() {

}

void CounterStrikeStyle::setCounterStrikeFont(QDialog* qDialog, int size) {
    QFontDatabase::addApplicationFont(PATH_TO_COUNTER_STRIKE_FONT);
    QFont CounterStrikeFont("Counter-Strike", size, QFont::Normal);
    qDialog->setFont(CounterStrikeFont);
}


void CounterStrikeStyle::setCounterStrikeFont(QWidget* qWidget, int size) {
    QFontDatabase::addApplicationFont(PATH_TO_COUNTER_STRIKE_FONT);
    QFont CounterStrikeFont("Counter-Strike", size, QFont::Normal);
    qWidget->setFont(CounterStrikeFont);
}
