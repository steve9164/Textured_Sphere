#-------------------------------------------------
#
# Project created by QtCreator 2016-06-28T18:27:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGL_Sphere
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    sphere.cpp \
    dialogeventhandlers.cpp \
    eventhandler.cpp

HEADERS  += dialog.h \
    sphere.h \
    dialogeventhandlers.h \
    eventhandler.h

FORMS    += dialog.ui

INCLUDEPATH += /usr/local/include
