#-------------------------------------------------
#
# Project created by QtCreator 2016-04-08T09:21:25
#webkitwidgets
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_single430
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    dialog.cpp \
    weather.cpp \
    mainwindow.cpp

HEADERS  += widget.h \
    dialog.h \
    weather.h \
    mainwindow.h

FORMS    += widget.ui \
    dialog.ui \
    weather.ui \
    mainwindow.ui

RESOURCES += \
    qt_photo.qrc
