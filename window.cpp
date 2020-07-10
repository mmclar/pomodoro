#include "window.h"

#ifndef QT_NO_SYSTEMTRAYICON

#include <QAction>
#include <QCoreApplication>
#include <QMenu>
#include <QTimer>
#include <ticktimer.h>

// When debugging, don't wait so long.
const int MS_PER_MINUTE =
    #ifdef QT_DEBUG
        500;
    #else
        1000 * 60;
    #endif

const int MSG_DISPLAY_DURATION_MS = 10000;
const int UPDATE_FREQUENCY_MS = 1000;

Window::Window() {
    trayIcon = new QSystemTrayIcon(this);
    trayIconMenu = new QMenu(this);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    runningAction = new QAction(tr("&Pomodoro is running"), this);
    runningAction->setEnabled(false);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    endPomAction = new QAction(tr("&End this pomodoro"), this);
    connect(quitAction, &QAction::triggered, qApp, [this]{ reset(); });

    ICON_READY = new QIcon(":/images/tomato.svg");
    ICON_RUNNING = new QIcon(":/images/green-tomato.svg");

    reset();

    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->show();
}

void Window::reset() {
    // Reset the menu to just the pom start items and quit
    trayIconMenu->clear();

    for (int i = 15; i <= 60; i += 15) {
        QString menuTitle = QString("%1 minutes").arg(i);
        QAction *pomAction = new QAction(menuTitle);
        connect(pomAction, &QAction::triggered, this, [this, i]{ Window::pomClicked(i); });
        trayIconMenu->addAction(pomAction);
    }

    trayIconMenu->addAction(quitAction);

    trayIcon->setIcon(*ICON_READY);
}

void Window::setVisible(bool visible) {
    // Always set visible false
    QDialog::setVisible(false && visible);
}

void Window::pomClicked(int minutes) {
    QString msgBody = QString("Timer set for %1 minutes").arg(minutes);
    trayIcon->showMessage("Pomodoro", msgBody, *ICON_RUNNING, MSG_DISPLAY_DURATION_MS);
    trayIcon->setIcon(*ICON_RUNNING);

    // Start the timer and set the tick and ding callbacks
    tickTimer = new TickTimer(this);
    connect(tickTimer, &TickTimer::tick, this, [this]{ Window::updatePomStatus(); });
    connect(tickTimer, &TickTimer::ding, this, [this]{ Window::timerUp(); });
    tickTimer->start(UPDATE_FREQUENCY_MS, minutes * MS_PER_MINUTE);
    updatePomStatus();

    trayIconMenu->clear();
    trayIconMenu->addAction(runningAction);
    trayIconMenu->addAction(endPomAction);
    trayIconMenu->addAction(quitAction);
}

void Window::updatePomStatus() {
    int millis = tickTimer->getRemainingMS();
    int seconds = millis / 1000;
    int minutes = seconds / 60;
    seconds = seconds % 60;
    QString formattedTime = QString("%1:%2").arg(minutes).arg(seconds, 2, 10, QChar('0'));
    runningAction->setText(QString("%1 remaining").arg(formattedTime));
}

void Window::timerUp() {
    QString msgBody = "Time's up!";
    // Show a message that doesn't fade away until the user address it
    trayIcon->showMessage("Pomodoro", msgBody, *ICON_READY, 0);
    reset();
}

#endif
