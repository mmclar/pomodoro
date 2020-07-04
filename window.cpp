#include "window.h"

#ifndef QT_NO_SYSTEMTRAYICON

#include <QAction>
#include <QCoreApplication>
#include <QMenu>
#include <QTimer>

const int MS_PER_MINUTE = 1000 * 60;

Window::Window() {
    trayIconMenu = new QMenu(this);
    ICON_READY = new QIcon(":/images/tomato.svg");
    ICON_RUNNING = new QIcon(":/images/green-tomato.svg");

    for (int i = 15; i <= 60; i += 15) {
        QString menuTitle = QString("%1 minutes").arg(i);
        QAction *pomAction = new QAction(menuTitle);
        connect(pomAction, &QAction::triggered, this, [this, i]{ Window::pomClicked(i); });
        trayIconMenu->addAction(pomAction);
    }

    QAction *quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(*ICON_READY);
    trayIcon->show();
}

void Window::setVisible(bool visible) {
    // Always set visible false
    QDialog::setVisible(false && visible);
}

void Window::pomClicked(int minutes) {
    QString msgBody = QString("Timer set for %1 minutes").arg(minutes);
    trayIcon->showMessage("Pomodoro", msgBody, *ICON_RUNNING);
    trayIcon->setIcon(*ICON_RUNNING);
    QTimer::singleShot(minutes * MS_PER_MINUTE, this, SLOT(timerUp()));
}

void Window::timerUp() {
    QString msgBody = "Time's up!";
    trayIcon->showMessage("Pomodoro", msgBody, *ICON_READY);
    trayIcon->setIcon(*ICON_READY);
}

#endif
