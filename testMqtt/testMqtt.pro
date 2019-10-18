QT += concurrent
TEMPLATE = app
QT += qml quick
QT += opengl
QT += gui
QT += quick
QT += network
QT += core
CONFIG += c++11
QT += multimedia
QT += core gui network


TRANSLATIONS = zh_CN.ts en_US.ts

QMAKE_CXXFLAGS_RELEASE += -g
QMAKE_CFLAGS_RELEASE += -g
QMAKE_LFLAGS_RELEASE = -mthreads

SOURCES += \
        main.cpp \
    mqtttest.cpp \
    mqttpacket.cpp

RESOURCES += qml.qrc

INCLUDEPATH += $$PWD/third/mqtt/include

LIBS += $$PWD/third/mqtt/lib/libQt5Mqttd.a \
        $$PWD/third/mqtt/lib/libQt5Mqtt.a \

HEADERS += \
    mqtttest.h \
    mqttpacket.h
