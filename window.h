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
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

private slots:
    static void pomClicked(int minutes);
};

#endif // QT_NO_SYSTEMTRAYICON

#endif
