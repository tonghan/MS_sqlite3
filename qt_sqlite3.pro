#-------------------------------------------------
#
# Project created by QtCreator 2016-01-11T10:06:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_sqlite3
TEMPLATE = app
LIBS += -lsqlite3
CONFIG +=console

SOURCES += main.cpp \
    login.cpp \
    student.cpp \
    addnumber.cpp \
    showlist.cpp

HEADERS  += \
    login.h \
    student.h \
    addnumber.h \
    showlist.h

FORMS    += \
    login.ui \
    student.ui \
    addnumber.ui \
    showlist.ui

RESOURCES += \
    iamge/image.qrc \
    iamge/image.qrc

DISTFILES += \
    iamge/backgroud.jpg
