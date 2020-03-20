#include "wintcpthread.h"

WinTcpThread::WinTcpThread(): QObject()
{
    WSAStartup(MAKEWORD(2,2),&mWasData);

    videoFrameMaxLen = 1024 * 3500;
    audioFrameMaxLen = 160;
}

void WinTcpThread::slot_createTcpConnect(QString ip,int port){

    mSocket = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(mSocket == INVALID_SOCKET){
        qDebug()<<"创建tcp连接失败";
        return;
    }

    qDebug() << ip;
    qDebug() << port;
    SOCKADDR_IN addr;
    addr.sin_family = PF_INET;
    addr.sin_port = htons((u_short)port);
    addr.sin_addr.S_un.S_addr = inet_addr(ip.toUtf8().data());//点分十进制转ip地址
    int val = ::connect(mSocket,(SOCKADDR*)&addr,sizeof(addr));
    int error;
    if( val == SOCKET_ERROR){
        qDebug()<<("连接失败！！！");
        error = WSAGetLastError();
        qDebug() << "connect error:" << error;
        return;
    }
    qDebug()<<(QString("连接成功"));

    recData();
    //信号槽连接
    //    connect(this,&Widget::isSend,mMsgThread,&MsgThread::dealSend);
    //    connect(mMsgThread,&MsgThread::isMsg,this,&Widget::dealMsg);
    //    connect(mMsgThread,&MsgThread::isClose,this,&Widget::dealClose);

}

void WinTcpThread::recData(){

    char buf[10240] = {0};
    while(true){


        //等待服务端回应
        int ret = ::recv(mSocket,buf,10240,0);
        //服务端关闭
        if( ret == 0){
            qDebug()<<"服务端guanbi";
            return;
        }
       // qDebug()<<"ret:"<<ret;
        readDataBuff.append(buf,ret);

        parseRecevieData();

        //            QTime time = QTime::currentTime();
        //            QString str = time.toString("hh:mm:ss");
        //            qDebug() << "buf:" << buf ;
        //            QString msg = QString("%1 收到消息[%2]").arg(str).arg(buf);

    }

}


void WinTcpThread::parseRecevieData()
{
    int needlen = 2;

    /*
        循环解析整个readDataBuff，把所有有效的数据都解析出来
        每次找到一个信息都会把包含该信息的字节数据删除
        needlen代表解析数据还需要的字节长度
        1、找头，
        2、找媒体信息类型
        3、找媒体裸流数据（消息回应）
    */

    QTime time;
    time.start();
    //qDebug()<<"解析开始："<<readDataBuff.length()<<" "<<needlen;
    while(readDataBuff.length() >= needlen)
    {
        //QMutexLocker lock(&parseMutex);


        if(!isFindHead)
        {

            if(readDataBuff.at(0) == D_SYNCDATA_HEAD0 && readDataBuff.at(1)==D_SYNCDATA_HEAD1)
            {

                readDataBuff.remove(0,2);
                isFindHead = true;
                needlen = 2;
            }else {
                readDataBuff.remove(0,1);
                continue;
            }
        }


        //找到头后，找媒体类型
        if(!isFindMediaType)
        {
            if(readDataBuff.length()>=needlen){
                int tmp = readDataBuff.at(1);
                mediaDataType =  tmp & 0x000000ff;
                readDataBuff.remove(0,2);


                if(mediaDataType >= MediaType_H264 && mediaDataType <= MediaType_MSG){

                    isFindMediaType = true;

                }else {//不合理的媒体类型则从新开始找头
                    resetAVFlag();
                    continue;
                }
            }
            else
                continue;
        }

        if(mediaDataType == MediaType_H264)
        {
            needlen = 28;

            if(!isSaveVideoInfo)
            {
                if(readDataBuff.length() >= needlen)
                {
                    m_streamDateLen = saveVideoInfo(readDataBuff);
                    isSaveVideoInfo = true;


                    if(m_streamDateLen > videoFrameMaxLen || m_streamDateLen <0)
                    {
                        qDebug()<<"视频帧数据长度异常:"<<m_streamDateLen;
                        resetAVFlag();
                        continue;
                    }
                }else
                    continue;
            }

            needlen = m_streamDateLen;

            if(readDataBuff.length()>=needlen)
            {

                //emit signal_writeMediaVideoQueue(readDataBuff.data(),m_streamDateLen,infoV,MediaDataProcess::mMediaVeidoType);
                quint64 ptsH = 0x00000000ffffffff & infoV.highPts;
                quint64 ptsL = 0x00000000ffffffff & infoV.lowPts;
                quint64 pts = ptsH *256 *255*256 + ptsL;



                //qDebug()<<"解析到视频";
                emit signal_sendH264(readDataBuff.data(),m_streamDateLen,pts);

                readDataBuff.remove(0,m_streamDateLen);
                resetAVFlag();

                needlen = 2;
                continue;

            }else{

                continue;
            }
        }else if(MediaType_G711A == mediaDataType){

            needlen = 28;
            if(!isSaveAudioInfo){

                if(readDataBuff.length() >= needlen)
                {
                    m_streamDateLen = saveAudioInfo(readDataBuff);
                    isSaveAudioInfo = true;

                    if(m_streamDateLen > audioFrameMaxLen)
                    {
                        qDebug()<<"音频数据长度异常:"<<m_streamDateLen;
                        resetAVFlag();
                        continue;
                    }


                }else
                    continue;
            }

            needlen = m_streamDateLen;
            if(m_streamDateLen > 0 && readDataBuff.length()>=needlen)
            {

                quint64 ptsH = 0x00000000ffffffff & infoA.highPts;
                quint64 ptsL = 0x00000000ffffffff & infoA.lowPts;
                quint64 pts = ptsH *256 *255*256 + ptsL;


               // qDebug()<<"解析到音频";
                emit signal_sendPcmALaw(readDataBuff.data(),m_streamDateLen,pts);

               // QThread::msleep(1);

                readDataBuff.remove(0,m_streamDateLen);

                m_streamDateLen = 2;
                resetAVFlag();
                continue;
            }else
                continue;
        }
        else if(MediaType_MSG  == mediaDataType)
        {

            needlen = 136;
            if(readDataBuff.length() >= needlen){
                int index = 0;
                QByteArray arrlen = readDataBuff.mid(index,4);
                int datalen = byteArr2Int(arrlen);
                index += 4;

                QByteArray arrstatuscode = readDataBuff.mid(index,4);
                int statuscode = byteArr2Int(arrstatuscode);
                index += 4;

                QByteArray arrDid = readDataBuff.mid(index,128);

                readDataBuff.remove(0,136);
                needlen = 2;
                resetAVFlag();
                continue;
            }else {
                continue;
            }
        }
        resetAVFlag();
        needlen = 2;
    }



   // qDebug()<<"解析耗时："<<time.elapsed()<<"ms";

}



int WinTcpThread::byteArr2Int(QByteArray arr)
{

    int index = 0;
    int i1 = 0x000000ff & arr.at(index++);
    int i2 = 0x000000ff & arr.at(index++);
    int i3 = 0x000000ff & arr.at(index++);
    int i4 = 0x000000ff & arr.at(index++);

    return (i1 + i2*256 + i3*65536 + i4*16777216);
}


int WinTcpThread::saveVideoInfo(QByteArray &arr)
{
    int index = 0;
    int fps = 0x000f & arr.at(index++);
    int rcmode = 0x000f & arr.at(index++);
    int frameType = 0x000f & arr.at(index++);
    int staty0 = 0x000f & arr.at(index++);
    //VideoReslution_T

    QByteArray arrW = arr.mid(index,4);
    int width = byteArr2Int(arrW);
    index += 4;


    QByteArray arrH = arr.mid(index,4);

    int height = byteArr2Int(arrH);

    index += 4;

    //  bitrate
    QByteArray arrBitrate = arr.mid(index,4);
    int bitrate =  byteArr2Int(arrBitrate);
    index += 4;
    //pts


    // qDebug()<< "bitrate:"<<bitrate<<"    rcmode"<<rcmode<<" fps"<<fps <<" width:"<<width<<"    height "<<height;
    index += 8;
    //裸流数据长度

    QByteArray arrDatalen = arr.mid(index,4);

    int datalen = byteArr2Int(arrDatalen);
    index += 4;

    memcpy(&infoV,arr.data(),sizeof (QueueAudioInputInfo_T));
    arr.remove(0,index);

    return datalen;
}
int WinTcpThread::saveAudioInfo(QByteArray &arr)
{

    //qDebug()<<"revice audio";
    int index = 0;
    QByteArray arrS = arr.mid(index,4);
    int samplerate = byteArr2Int(arrS);
    index += 4;

    QByteArray arrP = readDataBuff.mid(index,4);
    int prenum = byteArr2Int(arrP);
    index += 4;

    QByteArray arrB = readDataBuff.mid(index,4);
    int bitwidth = byteArr2Int(arrB);
    index += 4;

    QByteArray arrSoude = readDataBuff.mid(index,4);
    int soundmode = byteArr2Int(arrSoude);
    index += 4;

    QByteArray arrH = readDataBuff.mid(index,4);
    int highPts = byteArr2Int(arrH);
    index += 4;

    QByteArray arrL = readDataBuff.mid(index,4);
    int lowPts = byteArr2Int(arrL);
    index += 4;


    QByteArray arrDatalen = readDataBuff.mid(index,4);
    int datalen = byteArr2Int(arrDatalen);
    index += 4;

    memcpy(&infoA,arr.data(),sizeof (QueueAudioInputInfo_T));
    arr.remove(0,index);

    return datalen;
}

void WinTcpThread::resetAVFlag()
{
    m_streamDateLen = -1;
    mediaDataType = -1;
    isFindHead = false;
    isSaveAudioInfo = false;
    isSaveVideoInfo = false;
    isFindMediaType = false;
}


void WinTcpThread::tcpSendAuthentication(QString did,QString usrName,QString password)
{
    // qDebug()<<"did usrName password:"<<did<<"   "<<usrName<<"   "<<password;

    if(did != ""){
        //disconnect(tcpSocket,&QTcpSocket::readyRead,this,&WinTcpThread::slot_readData);
        QByteArray arr;

        unsigned int datelen = 128 + 64 +64;
        int datelen0 = (0x000000ff & datelen);
        int datelen1 = (0x000000ff & (datelen>>8));
        int datelen2 = (0x000000ff & (datelen>>16));
        int datelen3 = (0x000000ff & (datelen>>24));
        arr.append(D_SYNCDATA_HEAD0);
        arr.append(D_SYNCDATA_HEAD1);
        arr.append(Msg_GetPlay);
        arr.append(MediaType_MSG);
        arr.append(datelen0);
        arr.append(datelen1);
        arr.append(datelen2);
        arr.append(datelen3);
        arr.append(did);
        arr.append(128-did.size(),0);
        arr.append(usrName);
        arr.append(64-usrName.size(),0);
        arr.append(password);
        arr.append(64-password.size(),0);

        sendData(arr);
    }
}

void WinTcpThread::sendData(QByteArray &arr){

    //发送
    ::send(mSocket,arr.data(),arr.length() +1,0);
    int errorCode = WSAGetLastError();
    //连接超时
    if( errorCode == WSAECONNABORTED){

        qDebug()<<"发送失败 连接超时";
        return;
    }
}
