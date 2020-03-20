#include "ffmpegrtsp.h"

FFmpegRtsp::FFmpegRtsp(QObject *parent) : QObject(parent)
{

}

int FFmpegRtsp::initFfmpg(const char *rtsp)
{
    unsigned int    i;
    int             ret;

    ifmt_ctx = NULL;

    AVStream        *st = NULL;

    AVDictionary *optionsDict = NULL;
    av_register_all();                                                          // Register all codecs and formats so that they can be used.
            avformat_network_init();                                                    // Initialization of network components
            av_init_packet(&pkt);                                                       // initialize packet.
            pkt.data = NULL;
    pkt.size = 0;
    bool nRestart = false;
    AVStream *pVst;

    pVideoCodecCtx = NULL;
    pFrame = av_frame_alloc();
    pFrameRGB = av_frame_alloc();
    int got_picture;

    AVCodec *pVideoCodec = NULL;
    av_dict_set(&optionsDict, "rtsp_transport", "tcp", 0);                //采用tcp传输
            av_dict_set(&optionsDict, "stimeout", "2000000", 0);                  //如果没有设置stimeout，那么把ipc网线拔掉，av_read_frame会阻塞（时间单位是微妙）
            if ((ret = avformat_open_input(&ifmt_ctx, rtsp, 0, &optionsDict)) < 0) {            // Open the input file for reading.
                printf("Could not open input file '%s' (error '%s')\n", rtsp, av_make_error_string(errbuf, sizeof(errbuf), ret));
                                                                                     return -1;
                                                                                   }

    if ((ret = avformat_find_stream_info(ifmt_ctx, NULL)) < 0) {                // Get information on the input file (number of streams etc.).
                printf("Could not open find stream info (error '%s')\n", av_make_error_string(errbuf, sizeof(errbuf), ret));
        return -1;
    }

    for (i = 0; i < ifmt_ctx->nb_streams; i++) {                                // dump information
                av_dump_format(ifmt_ctx, i, rtsp, 0);
    }

    for (i = 0; i < ifmt_ctx->nb_streams; i++)
    {                                // find video stream index
                st = ifmt_ctx->streams[i];
        switch (st->codec->codec_type)
        {
        case AVMEDIA_TYPE_AUDIO: audio_st_index = i; break;
            case AVMEDIA_TYPE_VIDEO: video_st_index = i; break;
            default: break;
        }
    }
        if (-1 == video_st_index) {
            printf("No H.264 video stream in the input file\n");
            return -1;
        }

    if (!nRestart)
    {
        pVst = ifmt_ctx->streams[video_st_index];
        pVideoCodecCtx = pVst->codec;
        pVideoCodec = avcodec_find_decoder(pVideoCodecCtx->codec_id);
        if (pVideoCodec == NULL)
            return -1;
        if (avcodec_open2(pVideoCodecCtx, pVideoCodec, NULL) < 0)
            return -1;
    }
}
#include <QDebug>
#include <QThread>
void FFmpegRtsp::readStream()
{
    int ret;
    int got_picture = 0;
    qDebug()<<"Dsadsa";
    while (1)
    {
        do {
            ret = av_read_frame(ifmt_ctx, &pkt);                                // read frames
            if (pkt.stream_index == video_st_index)
            {
                //fprintf(stdout, "pkt.size=%d,pkt.pts=%lld, pkt.data=0x%x.", pkt.size, pkt.pts, (unsigned int)pkt.data);
                int av_result = avcodec_decode_video2(pVideoCodecCtx, pFrame, &got_picture, &pkt);

                if (av_result < 0)
                {
                    fprintf(stderr, "decode failed: inputbuf = 0x%x , input_framesize = %d\n", pkt.data, pkt.size);
                    return;
                }

                if (got_picture)
                {
                    int bytes = avpicture_get_size(AV_PIX_FMT_RGB24, pVideoCodecCtx->width, pVideoCodecCtx->height);
                    buffer_rgb = (uint8_t *)av_malloc(bytes);
                    avpicture_fill((AVPicture *)pFrameRGB, buffer_rgb, AV_PIX_FMT_RGB24, pVideoCodecCtx->width, pVideoCodecCtx->height);

                    img_convert_ctx = sws_getContext(pVideoCodecCtx->width, pVideoCodecCtx->height, pVideoCodecCtx->pix_fmt,
                                                     pVideoCodecCtx->width, pVideoCodecCtx->height, AV_PIX_FMT_BGR24, SWS_FAST_BILINEAR, NULL, NULL, NULL);
                    if (img_convert_ctx == NULL)
                    {

                        printf("can't init convert context!\n");
                        return;
                    }
                    sws_scale(img_convert_ctx, pFrame->data, pFrame->linesize, 0, pVideoCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);

                    imgPtr = new unsigned char[pVideoCodecCtx->width*pVideoCodecCtx->height*3/2];

                    memcpy(imgPtr,pFrame->data[0],pVideoCodecCtx->width*pVideoCodecCtx->height);
                    memcpy(imgPtr+pVideoCodecCtx->width*pVideoCodecCtx->height,pFrame->data[1],pVideoCodecCtx->width*pVideoCodecCtx->height/4);
                    memcpy(imgPtr+pVideoCodecCtx->width*pVideoCodecCtx->height*5/4,pFrame->data[2],pVideoCodecCtx->width*pVideoCodecCtx->height/4);

                    QThread::msleep(10);
                    emit signals_sendYuvData1(imgPtr,pVideoCodecCtx->width,pVideoCodecCtx->height);


                    qDebug()<<"dsadsa";

                    sws_freeContext(img_convert_ctx);
                    av_free(buffer_rgb);
                }
            }
        } while (ret == AVERROR(EAGAIN));

        if (ret < 0) {
            printf("Could not read frame ---(error '%s')\n", av_make_error_string(errbuf, sizeof(errbuf), ret));
            break;
        }
        av_packet_unref(&pkt);
    }

    if (NULL != ifmt_ctx) {
        avcodec_close(pVideoCodecCtx);
        avformat_close_input(&ifmt_ctx);
        av_free(pFrame);
        av_free(pFrameRGB);
        ifmt_ctx = NULL;
    }
}
void FFmpegRtsp::sendYuvData()
{

}

void FFmpegRtsp::sendImgData()
{

}
