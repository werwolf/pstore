#-------------------------------------------------
#
# Project created by QtCreator 2011-03-12T13:07:25
#
#-------------------------------------------------

QT       += core gui sql

TARGET = pstore
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    loginform.cpp \
    edbconnection.cpp \
    puser.cpp \
    padmin.cpp \
    pmanager.cpp

HEADERS  += mainwindow.h \
    loginform.h \
    edbconnection.h \
    puser.h \
    padmin.h \
    pmanager.h

FORMS    += mainwindow.ui \
    loginform.ui \
    padmin.ui \
    pmanager.ui

RESOURCES += \
    pstore.qrc
