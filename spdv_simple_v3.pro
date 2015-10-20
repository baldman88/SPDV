#-------------------------------------------------
#
# Project created by QtCreator 2015-08-12T15:43:33
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport printsupport

TARGET = spdv_simple_v3
TEMPLATE = app


SOURCES += main.cpp \
    crc16/crc16.cpp \
    mycombobox/mycombobox.cpp \
    plotwidget/plotwidget.cpp \
    portwidgetsimple/portwidgetsimple.cpp \
    qcustomplot/qcustomplot.cpp \
    recordwidget/recordwidget.cpp \
    uartmanager/uartmanager.cpp \
    mainwindow.cpp

HEADERS  += \
    crc16/crc16.hpp \
    mycombobox/mycombobox.hpp \
    plotwidget/plotwidget.hpp \
    portwidgetsimple/portwidgetsimple.hpp \
    qcustomplot/qcustomplot.hpp \
    recordwidget/recordwidget.hpp \
    uartmanager/uartmanager.hpp \
    mainwindow.hpp
