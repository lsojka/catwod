#-------------------------------------------------
#
# Project created by QtCreator 2015-04-22T23:47:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = catwod
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gridwidget.cpp \
    cell.cpp

HEADERS  += mainwindow.h \
    gridwidget.h \
    cell.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    backlog.txt
