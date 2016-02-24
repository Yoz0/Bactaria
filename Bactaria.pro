#-------------------------------------------------
#
# Project created by QtCreator 2016-02-10T17:22:54
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bactaria
TEMPLATE = app


SOURCES += main.cpp\
    hexacellboard.cpp \
    hexacell.cpp \
    gameview.cpp \
    gamemodel.cpp

HEADERS  += \
    hexacellboard.h \
    hexacell.h \
    gameview.h \
    gamemodel.h

FORMS    += mainwindow.ui
