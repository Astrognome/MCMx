#-------------------------------------------------
#
# Project created by QtCreator 2012-08-21T14:49:49
#
#-------------------------------------------------

QT       += core gui\
    webkit\
    network

TARGET = MCMx
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    worldbackup.cpp \
    filestuff.cpp \
    settings.cpp \
    general.cpp \
    networkops.cpp \
    launcher.cpp

HEADERS  += mainwindow.h \
    worldbackup.h \
    filestuff.h \
    settings.h \
    general.h \
    networkops.h \
    launcher.h

FORMS    += mainwindow.ui
