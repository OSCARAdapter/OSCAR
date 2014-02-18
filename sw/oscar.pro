HEADERS = src/mainwindow.h \
          src/devicethread.h \
          src/boardv1.h
SOURCES = src/mainwindow.cpp \
          src/devicethread.cpp \
          src/boardv1.cpp \
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
INCLUDEPATH += C:/libusbx-1.0.12-win/include/libusbx-1.0/
## TODO: add win32 only linking...
LIBS += C:/libusbx-1.0.12-win/MS64/dll/libusb-1.0.lib
}
unix {
INCLUDEPATH += /usr/include/libusb-1.0/
LIBS += -lusb-1.0
}
