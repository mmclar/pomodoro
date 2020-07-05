#include "ticktimer.h"
#include <QAction>
#include <QTimer>

TickTimer::TickTimer(QWidget *parent) : QWidget(parent)
{
}

void TickTimer::start(int tickMS, int dingMS) {
    this->tickMS = tickMS;
    this->dingMS = dingMS;
    tickTimer = new QTimer(this);
    dingTimer = new QTimer(this);
    tickCount = 0;
    connect(tickTimer, &QTimer::timeout, this, [this]{
        tickCount++;
        tick();
    });
    connect(dingTimer, &QTimer::timeout, this, [this]{
        ding();
        tickTimer->stop();
        dingTimer->stop();
    });
    tickTimer->start(tickMS);
    dingTimer->start(dingMS);
}

int TickTimer::getRemainingMS() {
    return dingMS - (tickCount * tickMS);
}
