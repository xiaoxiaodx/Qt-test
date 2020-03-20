#ifndef TCPWORKER_H
#define TCPWORKER_H


#define D_SYNCDATA_HEAD0 0x77
#define D_SYNCDATA_HEAD1 0x17
#define MAX_STREAM_MTU_SIZE 1450

#include <QObject>
#include <QTcpSocket>
#include <QThread>
#include <QHostAddress>
#include <QTimer>
#include <QImage>
#include <QFile>

#include "ffmpegcodec.h"
#include "common.h"
#include "util.h"

#define MAX_AUDIO_FRAME_SIZE 192000

class TcpWorker : public QObject
{
    Q_OBJECT
public:
    explicit TcpWorker(QString logId);
    ~TcpWorker();

signals:

    void signal_sendH264(char* vH264Arr,int arrLen,long long pts);
    void signal_sendPcmALaw(char* PcmALawArr,int arrLen,long long pts);
    void signal_sendPreparePlayAudio(int samplerate,int prenum,int bitwidth,int soundmode,long pts);

    void signal_readMediaQueue();
    void signal_waitTcpConnect(QString str);
    void signal_endWait();
    void signal_workFinished();

    void finish();
public slots:

    void slot_readData();
    void slot_tcpDisconnected();
    void slot_tcpConnected();


    void slot_timerConnectSer();
    void slot_disConnectSer();
    void slot_tcpSendAuthentication(QString did,QString name,QString pwd);
    void slot_tcpRecAuthentication(QString did,QString name,QString pwd);

    void slot_destory();

    void creatNewTcpConnect(QString ip,int port);


    void setLogIdetity(QString str);
    void startParsing();
    void stopParsing();

    void testState();
private:


    /*********************************/
    int saveVideoInfo(QByteArray &arr);
    int saveAudioInfo(QByteArray &arr);
    QueueVideoInputInfo_T infoV;
    QueueAudioInputInfo_T infoA;

    /*********************************/
  //  void writeDebugfile(QString filename,QString funname,int lineCount,QString strContent);
    int byteArr2Int(QByteArray arr);
    void parseRecevieData();

    void initVariable();
    void resetAVFlag();

    QTcpSocket *tcpSocket;

    QByteArray readDataBuff;
    bool isFindHead;
    bool isFindMediaType;
    bool isSaveVideoInfo;
    bool isSaveAudioInfo;
    bool isSendAudioData;
    int mediaDataType;
    int m_streamDateLen;

    int minLen;

    QString m_did;
    QString m_usrName;
    QString m_password;
    QString ip;
    quint16 port;

    QTimer *timerConnectSer;
    bool isReconnecting;



    QFile *audioSrc;

    int videoFrameMaxLen;
    int audioFrameMaxLen;

    QMutex parseMutex;

    bool isStartParsing;
    bool isCheckedDataLong;
    bool isConnected;
    bool isHavaData;

private:
    QString mlogId;
    void writeDebugfile(QString filename,QString funname,int lineCount,QString strContent);

    QList<QMap<QString,QVariant>>  listSendMsg;
};

#endif // TCPWORKER_H
