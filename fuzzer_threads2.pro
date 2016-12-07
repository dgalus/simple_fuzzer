#-------------------------------------------------
#
# Project created by QtCreator 2016-12-04T19:34:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fuzzer_threads2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Fuzzer.cpp \
    CpuUsage.cpp

HEADERS  += mainwindow.h \
        += ByteArray.h \
        += CrashedReport.h \
        += Helpers.h \
    Fuzzer.h \
    CpuUsage.h

FORMS    += mainwindow.ui
