#ifndef TICKTIMER_H
#define TICKTIMER_H

#include <QWidget>

class TickTimer : public QWidget
{
    Q_OBJECT
public:
    explicit TickTimer(QWidget *parent);
    void start(int tickMS, int dingMS);
    int getRemainingMS();

signals:
    void tick();
    void ding();

public slots:

private:
    QTimer *tickTimer;
    QTimer *dingTimer;
    int tickMS;
    int dingMS;
    int tickCount;
};

#endif // TICKTIMER_H
