#-------------------------------------------------
#
# Project created by QtCreator 2016-08-09T13:58:44
#
#-------------------------------------------------

QT       += core gui
QT += xlsx

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = excel_read
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

DISTFILES += \
    logo.rc

RC_FILE = \
  logo.rc
