#-------------------------------------------------
#
# Project created by QtCreator 2014-02-17T19:23:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game_board
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    player.cpp \
    cards.cpp \
    bank.cpp

HEADERS  += mainwindow.h \
    player.h \
    cards.h \
    bank.h

FORMS    += mainwindow.ui
