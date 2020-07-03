#ifndef WINDOW_H
#define WINDOW_H

#include <QSystemTrayIcon>

#ifndef QT_NO_SYSTEMTRAYICON

#include <QDialog>

QT_BEGIN_NAMESPACE
class QAction;
QT_END_NAMESPACE

class Window : public QDialog
{
    Q_OBJECT

public:
    Window();
    void setVisible(bool visible) override;

private:
    void createActions();
    void createTrayIcon();

    QAction *startPomodoroAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
};

#endif // QT_NO_SYSTEMTRAYICON

#endif
