#include "decodethread.h"

#include <QFile>
#include <QDir>
#include <QDebug>
DecodeThread::DecodeThread(QObject *parent)
{

}

void DecodeThread::setUrl(QString url)
{
    _url = url;
}

void DecodeThread::run()
{


    unsigned char *nv12Ptr = nullptr;
    int width = 0, height = 0;
    unsigned long long timestamp = 0;

    QDir dir;
    qDebug()<<dir.currentPath();

    QFile file("dmjYUV1.yuv");


    if(file.open(QFile::ReadOnly)){

    }else {
        return;
    }

     arr = file.readAll();

    imgPtr = (unsigned char*)arr.data();
    videoW = 1920;
    videoH = 1080;



    qDebug()<<"数据长度："<<arr.length();
//    while ( !isInterruptionRequested())
//    {
//        QByteArray arr1;
//        for (int i=0;i<arr.size();i++) {
//            arr1.append(arr.at(i));
//        }
//        imgPtr = (unsigned char*)arr1.data();
//        videoW = 1920;
//        videoH = 1080;
//        QThread::msleep(2);
//    }
}
