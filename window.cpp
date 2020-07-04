#include "window.h"

#ifndef QT_NO_SYSTEMTRAYICON

#include <QAction>
#include <QCoreApplication>
#include <QMenu>

Window::Window()
{
    trayIconMenu = new QMenu(this);

    for (int i = 5; i <= 60; i += 5) {
        QString menuTitle = QString("%1 minutes").arg(i);
        QAction *pomAction = new QAction(menuTitle);
        connect(pomAction, &QAction::triggered, this, [i]{ Window::pomClicked(i); });
        trayIconMenu->addAction(pomAction);
    }

    QAction *quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/images/tomato.svg"));
    trayIcon->show();
}

void Window::setVisible(bool visible)
{
    // Always set visible false
    QDialog::setVisible(false && visible);
}

void Window::pomClicked(int minutes) {
    int j = minutes;
    // TODO: Use the minutes to show a message, then start the timer
}

#endif
