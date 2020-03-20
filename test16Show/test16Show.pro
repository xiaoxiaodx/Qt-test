QT += quick multimedia core network
CONFIG += c++11



# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    mediabase.cpp \
    renderthread.cpp \
    texturenode.cpp \
    playaudio.cpp \
    tcpworker.cpp \
    mydevice.cpp \
    ffmpegcodec.cpp \
    nv12render.cpp \
    wintcpthread.cpp \
    sendmsgqueue.cpp \
    util.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    mediabase.h \
    renderthread.h \
    texturenode.h \
    playaudio.h \
    tcpworker.h \
    mydevice.h \
    ffmpegcodec.h \
    common.h \
    nv12render.h \
    wintcpthread.h \
    sendmsgqueue.h \
    util.h




INCLUDEPATH += $$PWD/third/ffmpeg64/include
LIBS += -lpthread libwsock32 libws2_32
LIBS += $$PWD/third/ffmpeg64/lib/avcodec.lib \
        $$PWD/third/ffmpeg64/lib/avdevice.lib \
        $$PWD/third/ffmpeg64/lib/avfilter.lib \
        $$PWD/third/ffmpeg64/lib/avformat.lib \
        $$PWD/third/ffmpeg64/lib/avutil.lib \
        $$PWD/third/ffmpeg64/lib/postproc.lib \
        $$PWD/third/ffmpeg64/lib/swresample.lib \
        $$PWD/third/ffmpeg64/lib/swscale.lib

