#include "window.h"

#ifndef QT_NO_SYSTEMTRAYICON

#include <QAction>
#include <QCoreApplication>
#include <QMenu>

Window::Window()
{
    createActions();
    createTrayIcon();
}

void Window::setVisible(bool visible)
{
    // Don't do anything here; we don't want the window to be visible.
}

void Window::createActions()
{
    startPomodoroAction = new QAction(tr("Start pomodoro"), this);
    connect(startPomodoroAction, &QAction::triggered, this, &QWidget::hide);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void Window::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(startPomodoroAction);
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/images/tomato.svg"));
    trayIcon->show();
}

#endif
