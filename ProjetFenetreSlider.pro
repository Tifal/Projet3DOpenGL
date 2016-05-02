QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGL2Fonctionnel
TEMPLATE = app


SOURCES += main.cpp \
    displaywindow.cpp \
    programwindow.cpp \
    data.cpp

HEADERS  += displaywindow.h \
    programwindow.h \
    data.h
