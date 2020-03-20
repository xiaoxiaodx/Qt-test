#ifndef WINTCPTHREAD_H
#define WINTCPTHREAD_H

#include <QObject>
#include <windows.h>
#include <winsock2.h>
#include <QTime>
#include <QDebug>
#include "common.h"
#include <QThread>
class WinTcpThread : public QObject
{
    Q_OBJECT
public:
    explicit WinTcpThread();
    void recData();

signals:
    void signal_sendH264(char* vH264Arr,int arrLen,long long pts);
    void signal_sendPcmALaw(char* PcmALawArr,int arrLen,long long pts);

public slots:

    void slot_createTcpConnect(QString ip,int port);
    void tcpSendAuthentication(QString did,QString name,QString pwd);
private:

    void sendData(QByteArray &arr);
    void resetAVFlag();

    /*********************************/
    int saveVideoInfo(QByteArray &arr);
    int saveAudioInfo(QByteArray &arr);
    QueueVideoInputInfo_T infoV;
    QueueAudioInputInfo_T infoA;

    /*********************************/
    int byteArr2Int(QByteArray arr);
    void parseRecevieData();


    int videoFrameMaxLen;
    int audioFrameMaxLen;

    SOCKET mSocket;
    WSADATA mWasData;

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
};



#endif // WINTCPTHREAD_H
