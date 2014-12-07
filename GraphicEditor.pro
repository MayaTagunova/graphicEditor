#-------------------------------------------------
#
# Project created by QtCreator 2014-12-04T11:09:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphicEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    toolfactory.cpp \
    canvas.cpp \
    genericbrush.cpp \
    imageedit.cpp

HEADERS  += mainwindow.h \
    toolfactory.h \
    tool.h \
    canvas.h \
    genericbrush.h \
    imageedit.h

FORMS    += graphiceditor.ui

QMAKE_CXXFLAGS += -std=c++1y

RESOURCES += graphiceditor.qrc
