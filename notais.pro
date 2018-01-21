
TEMPLATE = app

QT = core gui widgets

CONFIG += c++14

LIBS += -lrtmidi -lm -lrtaudio

SOURCES += src/main.cc
HEADERS += src/gui/midiinput.hh
SOURCES += src/gui/midiinput.cc
HEADERS += src/gui/keyboard.hh
SOURCES += src/gui/keyboard.cc
HEADERS += src/gui/audiooutput.hh
SOURCES += src/gui/audiooutput.cc
HEADERS += src/gui/mainwindow.hh
SOURCES += src/gui/mainwindow.cc

OBJECTS_DIR = .buildfiles
MOC_DIR = .buildfiles

TARGET = notais