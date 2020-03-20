
#ifndef Mediabase_H
#define Mediabase_H
#include <QQuickPaintedItem>
#include <QImage>
#include <QList>
#include <QTimer>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QSGSimpleTextureNode>
#include <QDateTime>
#include <QDir>

#include <QQuickWindow>
#include "tcpworker.h"
#include "playaudio.h"


#include "renderthread.h"
#include "wintcpthread.h"

#include <util.h>
class Mediabase : public QQuickItem
{
    Q_OBJECT
    QML_PROPERTY(QVariant,logIdentity)
public:
    Q_INVOKABLE void sendAuthentication(QString did,QString name,QString pwd);
    Q_INVOKABLE void connectServer(QString ip,QString port);
    Q_INVOKABLE void disConnectServer();
    Q_INVOKABLE void funPlayAudio(bool isPlay);
    Q_INVOKABLE void funRecordVedio(bool isRecord);
    Q_INVOKABLE void funScreenShot();

    Q_INVOKABLE void funSetShotScrennFilePath(QString str);
    Q_INVOKABLE void funSetRecordingFilePath(QString str);



    explicit Mediabase();
    ~Mediabase();

signals:
    //tcp
    void signal_connentSer(QString ip,int port);
    void signal_disconnentSer();
    void signal_tcpSendAuthentication(QString did,QString name,QString pwd);
    void signal_destoryTcpWork();
    //qml
    void signal_loginStatus(QString msg);
    void signal_waitingLoad(QString msgload);
    void signal_endLoad();
    //audio
    void signal_stopPlayAudio();
    void signal_startAudio(bool isEnd);

    void signal_playAudio(unsigned char * buff,int len,long pts);
    void signal_preparePlayAudio(int samplerate,int prenum,int bitwidth,int soundmode,long pts);
    //p2p
    void signals_p2pDowork();
    //
    void signal_update();
    //record
    void signal_recordAudio(char *buff,int len,long long tempTime);
    void signal_recordVedio(char *buff,int len,long long tempTime);
    void signal_startRecord(QString did,long long tempTime);
    void signal_endRecord();
    void signal_setRecordingFilePath(QString str);




public slots:
    void slot_trasfer_waitingLoad(QString msgload);
    void slot_trasfer_endLoad();


    void slot_recH264(char *buff,int len,quint64 time);
    void slot_recPcmALaw(char *buff,int len,quint64 time);

    void slot_reconnectP2p();
    void slot_timeout();
    void sendWaitLoad(bool &isWaiting);
    void ready();



protected:
    QSGNode* updatePaintNode(QSGNode *old, UpdatePaintNodeData *);
private:

    void createTcpThread();
    void createP2pThread();
    void createMp4RecordThread();
    void createFFmpegDecodec();
    void creatDateProcessThread();
    void createPlayAudio();
    void createAviRecord();
    void createWinTcpThread();

    void initVariable();

    QThread *m_readThread;
    TcpWorker *worker;


    QThread *m_winSockThread;
    WinTcpThread *winTcpWorker;



    FfmpegCodec *pffmpegCodec;


    PlayAudio *playAudio;
    QThread *playAudioThread;


    QImage *m_Img;


    bool isImgUpdate;

    int minBuffLen;

    bool isPlayAudio;
    bool isRecord;
    bool isStartRecord;//是否启动录像
    bool isScreenShot;
    bool isAudioFirstPlay;
    bool isFirstData;


    quint64 preAudioTime;


    void writeDebugfile(QString filenam,int lineCount,QString strContent);

    yuvInfo yuvData;
    QList<yuvInfo> listYuv;
    QString mTcpIp;
    int mTcpPort;
    QString mDid;
    QString mAccount;
    QString mPassword;

    QString mshotScreenFilePath;

    RenderThread *m_renderThread{nullptr};
};

#endif // Mediabase_H
