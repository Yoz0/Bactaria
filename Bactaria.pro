#-------------------------------------------------
#
# Project created by QtCreator 2016-02-10T17:22:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bactaria
TEMPLATE = app


SOURCES += main.cpp\
    game.cpp \
    hexacellboard.cpp \
    hexacell.cpp

HEADERS  += \
    game.h \
    hexacellboard.h \
    hexacell.h

FORMS    += mainwindow.ui
