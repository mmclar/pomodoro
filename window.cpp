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
//        connect(pomAction, &QAction::triggered, qApp, &Window::pom(i));
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
    // Don't do anything here; we don't want the window to be visible.
}

void Window::pom(int minutes) {
    int j = minutes;
}

#endif
