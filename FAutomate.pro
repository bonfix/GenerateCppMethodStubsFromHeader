#-------------------------------------------------
#
# Project created by QtCreator 2015-09-11T18:02:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FAutomate
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dataobject.cpp \
    field.cpp \
    sourcegenerator.cpp

HEADERS  += mainwindow.h \
    dataobject.h \
    field.h \
    sourcegenerator.h

QT += sql
FORMS    += mainwindow.ui

CONFIG += c++11
CONFIG += console
