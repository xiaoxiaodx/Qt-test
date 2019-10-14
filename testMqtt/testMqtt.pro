QT += quick
CONFIG += c++11
QT += core gui network

DEFINES += QT_DEPRECATED_WARNINGS



SOURCES += \
        main.cpp \
    mqtttest.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/third/mqtt/include

LIBS += $$PWD/third/mqtt/lib/libQt5Mqttd.a \
        $$PWD/third/mqtt/lib/libQt5Mqtt.a \

HEADERS += \
    mqtttest.h
