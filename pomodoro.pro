HEADERS       = window.h \
    ticktimer.h
SOURCES       = main.cpp \
                window.cpp \
    ticktimer.cpp
RESOURCES     = pomodoro.qrc \
    pomodoro.qrc

QT += widgets
requires(qtConfig(combobox))

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/desktop/systray
INSTALLS += target
