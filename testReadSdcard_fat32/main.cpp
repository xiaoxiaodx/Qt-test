#include "mainwindow.h"
#include <QApplication>
#include "mbr_info.h"
#include <QTextCodec>
#include <QString>
#include "utils.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


//    QString str1111 = "fdsfd";
    QTextCodec *codec = QTextCodec::codecForName("UTF-16");
//    QByteArray ba1 = codec->fromUnicode(str1111);

//    qDebug()<<"test1 "<<Utils::bytes2stringHex(ba1.data(),12);

//    QString str1;
//    char msg[] = {0xb0 ,0x65, 0xfa, 0x5e, 0x87, 0x65, 0xf6,0x4e,0x39,0x59};

//    char msg1[] = {0x66 ,0x00, 0x64, 0x00, 0x73, 0x00, 0x66,0x00,0x64,0x00};

//    char msg1[] = {0x03 ,0x69, 0x81, 0x8a, 0x50, 0xa7, 0x87,0x27};
//    QByteArray arr;
//    for(int i =0;i<8;i++)
//        arr.append(msg1[i]);



//    QString str1 = codec->toUnicode(arr);
//    QString str2 = QString::fromLocal8Bit(msg1,10);
//    QString str3 = "";
//    QString str4 = QString::fromLatin1(msg1,10);
//    QString str5 = QString::fromUtf8(arr);
//    qDebug()<<"test2 "<<str1 <<" "<<str2<<" "<<str3<<" "<<str4<<" "<<str5;




    MainWindow w;
    w.show();


    return a.exec();
}
