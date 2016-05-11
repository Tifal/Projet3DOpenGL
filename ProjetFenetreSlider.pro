QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGL2Fonctionnel
TEMPLATE = app


HEADERS += \
    coordinateswindow.h \
    data.h \
    displaywindow.h \
    marker.h \
    programwindow.h

SOURCES += \
    coordinateswindow.cpp \
    data.cpp \
    displaywindow.cpp \
    marker.cpp \
    programwindow.cpp \
    main.cpp
