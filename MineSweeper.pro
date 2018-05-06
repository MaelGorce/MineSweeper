#-------------------------------------------------
#
# Project created by QtCreator 2018-05-05T13:56:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MineSweeper
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    MS_Main.cc \
    MS_CMainwindow.cc \
    MS_CMenubar.cc \
    MS_CConfiguration.cc \
    MS_CSquare.cc

HEADERS += \
    MS_CMainwindow.hh \
    MS_CMenubar.hh \
    MS_Traces.hh \
    MS_CConfiguration.hh \
    MS_CSquare.hh

FORMS +=
