#-------------------------------------------------
#
# Project created by QtCreator 2018-01-19T09:37:39
#
#-------------------------------------------------
# Qt shared
QT_CI_JENKINS_HOME=$$(JENKINS_HOME)
!isEmpty(QT_CI_JENKINS_HOME) {
    message("Qt CI environment detected, suppressing example registration")
    CONFIG += qaxserver_no_postlink
}

TEMPLATE = app
TARGET   = ActiveX
CONFIG += warn_off
QT += core widgets axserver gui


SOURCES += \
        main.cpp \
        activex.cpp \
    Video/glyuvwidget.cpp \
    Video/ffmpegrtsp.cpp


HEADERS += \
        activex.h \
    Video/glyuvwidget.h \
    Video/ffmpegrtsp.h


FORMS += \
        activex.ui

RC_FILE  = ActiveX.rc
DEF_FILE = ActiveX.def

INCLUDEPATH += $$PWD/ffmpeg64/include
#LIBS += -lpthread libwsock32 libws2_32
LIBS += $$PWD/ffmpeg64/lib/avcodec.lib \
        $$PWD/ffmpeg64/lib/avdevice.lib \
        $$PWD/ffmpeg64/lib/avfilter.lib \
        $$PWD/ffmpeg64/lib/avformat.lib \
        $$PWD/ffmpeg64/lib/avutil.lib \
        $$PWD/ffmpeg64/lib/postproc.lib \
        $$PWD/ffmpeg64/lib/swresample.lib \
        $$PWD/ffmpeg64/lib/swscale.lib
