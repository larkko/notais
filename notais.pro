
TEMPLATE = app

QT = core gui widgets

LIBS += -lrtmidi

SOURCES += src/main.cc
HEADERS += src/gui/mainwindow.hh
SOURCES += src/gui/mainwindow.cc

OBJECTS_DIR = .buildfiles
MOC_DIR = .buildfiles

TARGET = notais