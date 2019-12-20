#-------------------------------------------------
#
# Project created by QtCreator 2019-04-18T17:49:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReadSdcard_fat32
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mbr_info.cpp \
    partitioninfo.cpp \
    fat_fileinfo.cpp \
    dbr_info.cpp \
    fat_tableinfo.cpp \
    fat_dataarea.cpp \
    directoryiteminfo.cpp \
    fat_fileitem.cpp

HEADERS  += mainwindow.h \
    mbr_info.h \
    partitioninfo.h \
    fat_fileinfo.h \
    utils.h \
    dbr_info.h \
    fat_tableinfo.h \
    fat_dataarea.h \
    directoryiteminfo.h \
    fat_fileitem.h

FORMS    += mainwindow.ui

RESOURCES += \
    img.qrc

DISTFILES +=
