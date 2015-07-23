#-------------------------------------------------
#
# Project created by QtCreator 2015-07-09T10:39:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fingerprintapp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fingerprint.cpp

HEADERS  += mainwindow.h \
    ftrScanAPI.h \
    fingerprint.h

FORMS    += mainwindow.ui

unix:!macx|win32: LIBS += -lScanAPI
