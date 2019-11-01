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



HEADERS += \
    mqtttest.h \
    mqttpacket.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/third/mqtt/lib/ -lQt5Mqtt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/third/mqtt/lib/ -lQt5Mqttd

INCLUDEPATH += $$PWD/third/mqtt/include
DEPENDPATH += $$PWD/third/mqtt/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/third/mqtt/lib/libQt5Mqtt.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/third/mqtt/lib/libQt5Mqttd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/third/mqtt/lib/Qt5Mqtt.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/third/mqtt/lib/Qt5Mqttd.lib
