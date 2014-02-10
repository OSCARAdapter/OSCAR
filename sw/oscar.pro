HEADERS = src/mainwindow.h
SOURCES = src/mainwindow.cpp \
          src/main.cpp
FORMS   = ui/mainwindow.ui
OBJECTS_DIR = build
MOC_DIR     = build
UI_DIR      = build
DESTDIR     = bin
RESOURCES = ui/oscar.qrc

QT += widgets
win32 {
QT += winextras
}
