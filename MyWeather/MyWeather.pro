#-------------------------------------------------
#
# Project created by QtCreator 2016-08-15T15:21:51
#
#-------------------------------------------------

QT       += core gui network script sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyWeather
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

DISTFILES += \
    icon.rc

RC_FILE += \
    icon.rc

RESOURCES += \
    images.qrc
