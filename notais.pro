
TEMPLATE = app

QT = core gui widgets

CONFIG += c++14

LIBS += -lrtmidi -lm -lrtaudio

SOURCES += src/main.cc
HEADERS += src/lib/audio/audiodata.hh
SOURCES += src/lib/audio/audiodata.cc
HEADERS += src/lib/audio/audiosource.hh
SOURCES += src/lib/audio/audiosource.cc
HEADERS += src/lib/audio/oscillator.hh
SOURCES += src/lib/audio/oscillator.cc
HEADERS += src/lib/audio/adjustableaudiosource.hh
SOURCES += src/lib/audio/adjustableaudiosource.cc
HEADERS += src/lib/project/project.hh
SOURCES += src/lib/project/project.cc
HEADERS += src/lib/tuning/tuning.hh
HEADERS += src/lib/tuning/equaltemperament.hh
SOURCES += src/lib/tuning/equaltemperament.cc
HEADERS += src/gui/midiinput.hh
SOURCES += src/gui/midiinput.cc
HEADERS += src/gui/keyboard.hh
SOURCES += src/gui/keyboard.cc
HEADERS += src/gui/keyboardwidget.hh
SOURCES += src/gui/keyboardwidget.cc
HEADERS += src/gui/projectwidget.hh
SOURCES += src/gui/projectwidget.cc
HEADERS += src/gui/arrowselectorwidget.hh
SOURCES += src/gui/arrowselectorwidget.cc
HEADERS += src/gui/audiooutput.hh
SOURCES += src/gui/audiooutput.cc
HEADERS += src/gui/mainwindow.hh
SOURCES += src/gui/mainwindow.cc

OBJECTS_DIR = .buildfiles
MOC_DIR = .buildfiles

TARGET = notais