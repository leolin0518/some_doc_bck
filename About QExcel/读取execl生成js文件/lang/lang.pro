#-------------------------------------------------
#
# Project created by QtCreator 2016-03-21T15:44:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lang
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qexcel.cpp

HEADERS  += mainwindow.h \
    qexcel.h

FORMS    += mainwindow.ui
CONFIG   += qaxcontainer  #for excel
