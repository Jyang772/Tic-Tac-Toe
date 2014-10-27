#-------------------------------------------------
#
# Project created by QtCreator 2014-10-26T01:32:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += console

TARGET = TTT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    tictactoe.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    tictactoe.h

FORMS    += mainwindow.ui \
    dialog.ui
