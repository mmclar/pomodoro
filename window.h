#ifndef WINDOW_H
#define WINDOW_H

#include <QSystemTrayIcon>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QDialog>
#include "ticktimer.h"

QT_BEGIN_NAMESPACE
class QAction;
QT_END_NAMESPACE

class Window : public QDialog {
    Q_OBJECT

public:
    Window();
    void setVisible(bool visible) override;

private:
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    TickTimer *tickTimer;
    QAction *quitAction;
    QAction *runningAction;
    QAction *endPomAction;
    QIcon *ICON_READY;
    QIcon *ICON_RUNNING;

private slots:
    void pomClicked(int minutes);
    void reset();
    void updatePomStatus();
    void timerUp();
};

#endif // QT_NO_SYSTEMTRAYICON

#endif
