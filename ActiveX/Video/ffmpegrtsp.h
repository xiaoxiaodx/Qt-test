#ifndef FFMPEGRTSP_H
#define FFMPEGRTSP_H

#include <QObject>
extern "C"{
#include "libavformat/avformat.h"
#include "libavutil/mathematics.h"
#include "libavutil/time.h"
#include "libswscale/swscale.h"
}
class FFmpegRtsp : public QObject
{
    Q_OBJECT
public:
    explicit FFmpegRtsp(QObject *parent = nullptr);
     int initFfmpg(const char *);
signals:
    void signals_sendYuvData1(uchar *ptr,uint resolutionW,uint resolutionH);
public slots:
    void readStream();
private:

    AVFormatContext *ifmt_ctx = NULL;
    AVPacket        pkt;
    int             video_st_index = -1;
    int             audio_st_index = -1;
    AVFrame         *pFrameRGB ;
    AVFrame         *pFrame;
    uint8_t* buffer_rgb = NULL;
    SwsContext      *img_convert_ctx = NULL;
    AVCodecContext *pVideoCodecCtx = NULL;
    char            errbuf[64];
    unsigned char* imgPtr={0};

    void sendYuvData();
    void sendImgData();
};

#endif // FFMPEGRTSP_H
