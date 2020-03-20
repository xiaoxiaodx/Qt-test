#include "mydevice.h"
#include <QDebug>
#include <QThread>
MyDevice::MyDevice(QByteArray *arr)
{
    data_pcm = arr;
    this->open(QIODevice::ReadOnly ); // 为了解决QIODevice::read (QIODevice): device not open
    len_written = 0;
}

MyDevice::~MyDevice()
{
    this->close();
}

qint64 MyDevice::readData(char *data, qint64 maxlen) // data为声卡的数据缓冲区地址， maxlen为声卡缓冲区最大能存放的字节数
{
   // qDebug()<<"readData thread thread:"<<QThread::currentThreadId()<<"  "<<data_pcm->length() <<"   "<< maxlen;
    int arrLen = data_pcm->length();
//    if(arrLen == 0){
//        data_pcm->append(1764,0);
//        arrLen = 1764;
//        qDebug()<<"readData arrLen == 0";
//        memset(data,0,1764);
//        return 1764;
//    }
    //计算未播放的数据的长度
    qint64 len = arrLen> maxlen? maxlen : arrLen;
    qDebug()<<"readData maxlen "<<arrLen<<"  "<<maxlen<<"   "<<len;
    memcpy(data, data_pcm->data(), len); //把要播放的pcm数据存入声卡缓冲区里
    data_pcm->remove(0,len);

    return len;
}

qint64 MyDevice::writeData(const char *data, qint64 len)
{
}
