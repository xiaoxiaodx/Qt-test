#include "directoryiteminfo.h"
#include <QDebug>

DirectoryItemInfo::DirectoryItemInfo()
{

}

int DirectoryItemInfo::simpleParse(char *directoryItem,int &directirtNum,int &isLastDirectoy)
{

    if(directoryItem[0] == 0)//文件目录结束
        return End;

    char item = directoryItem[11];

    switch(item)
    {
    case 0xe5://删除
        return Delete;
    case 0x0f://长目录
    {
        int num = 0x1f & directoryItem[0];
        isLastDirectoy = (item>>7) & 0x00000001;
        directirtNum = num;
        return LongDirectory;
    }
    case 0x00://读写
        return ReadWrite;
    case 0x01://只读
        return OnlyRead;
    case 0x02://隐藏
        return Hide;
    case 0x04://系统
        return System;
    case 0x08://卷标
        return Label;
    case 0x10://子目录
        return Subdirectory;
    case 0x20://归档
        return Archive;

    }
    return Invalid;


}

bool DirectoryItemInfo::parseDirectoryItem_L(char *directoryItem,int count)//解析长文件名目录项
{


    int directorySize = count/32;

    for(int i=0;i<directorySize;i+=32)
    {
        if(i < directorySize-1)
            parseDirectoryItem_LSingle(directoryItem,i);
        else
            parseDirectoryItem_S(directoryItem,i);
    }

}
bool DirectoryItemInfo::parseDirectoryItem_LSingle(char *directoryItem ,int index1)
{

    int index = index1;

    char ch1 = directoryItem[index++];
    bool isLastDirctory = (ch1>>7) & 0x01;

    int directirtNum = 0x0000001f & ch1;

    char unicodeName1[10];

    for(int i =0;i<10;i++)
        unicodeName1[i] = directoryItem[index++];

    int flag_longDir = 0x000000ff & directoryItem[index++];
    if(flag_longDir == 11)
        qDebug()<<"是长文件目录";
    else
        qDebug()<<"不是长文件目录";

    index ++ ;

    int checkValue = 0x000000ff & directoryItem[index++];

    char unicodeName2[12];
    for(int i =0;i<12;i++)
        unicodeName2[i] = directoryItem[index++];

    int startCluster = 0x000000ff & directoryItem[index++] +  (0x000000ff & directoryItem[index++])*256;

    char unicodeName3[4];

    for(int i =0;i<4;i++)
        unicodeName3[i] = directoryItem[index++];

}


//QString fileName;
//QString fileExtensionName;
//char fileAttr;
//QString fileCreate_ms;
//QString fileCreate_time;
//QString fileCreate_date;
//QString fileAccess_date;//文件最后访问日期
//unsigned short fileStartClusterNum_H16;
//QString fileLastRevise_time;
//QString fileLastRevise_date;
//unsigned short fileStartClusterNum_L16;
//unsigned short fileLength;
bool DirectoryItemInfo::parseDirectoryItem_S(char *directoryItem,int index1)
{
    int index = index1;

    QByteArray arr;
    for(int i=index1;i<32;i++)
        arr.append(directoryItem[i]);

    //qDebug()<<"parseDirectoryItem_S :"<<arr.toHex();
    //name
    char tmpname[8] = {0};
    for(int i=0;i<8;i++)
        tmpname[i] = directoryItem[index++];
    fileName = QString::fromLocal8Bit(tmpname);

    //extension
    char tmpextensionName[3] = {0};
    for(int i=0;i<3;i++)
        tmpextensionName[i] = directoryItem[index++];
    fileExtensionName = QString::fromLocal8Bit(tmpextensionName);

    fileAttr = directoryItem[index++];
    index++;//系统保留

    short tmp_createms = 0x00ff & directoryItem[index++];
    fileCreate_ms = QString::number(tmp_createms*10%1000);

    short tmp_createtime = (0x00ff & directoryItem[index++]) + (0x00ff & directoryItem[index++])*256;
    fileCreate_time = formatTime(tmp_createtime,tmp_createms/100);

    short tmp_createdate = (0x00ff & directoryItem[index++]) + (0x00ff & directoryItem[index++])*256;
    fileCreate_date = formatDate(tmp_createdate);

    short tmp_accessDate = (0x00ff & directoryItem[index++]) + (0x00ff & directoryItem[index++])*256;
    fileAccess_date = formatDate(tmp_accessDate);

    fileStartClusterNum_H16 = (0x00ff & directoryItem[index++]) + (0x00ff & directoryItem[index++])*256;

    short tmp_lastReviseTime = (0x00ff & directoryItem[index++]) + (0x00ff & directoryItem[index++])*256;
    fileLastRevise_time = formatTime(tmp_lastReviseTime,0);

    short tmp_lastReviseData = (0x00ff & directoryItem[index++]) + (0x00ff & directoryItem[index++])*256;
    fileLastRevise_date = formatDate(tmp_lastReviseData);

    fileStartClusterNum_L16 = (0x00ff & directoryItem[index++]) + (0x00ff & directoryItem[index++])*256;

    fileLength = (0x000000ff & directoryItem[index++]) + (0x000000ff & directoryItem[index++])*256 + (0x000000ff & directoryItem[index++])*256*256 + (0x000000ff & directoryItem[index++])*256*256*256;
}

QString DirectoryItemInfo::formatTime(short buff,int msOffset)
{
    short tmp_time = buff;
    int hour = 0x0000001f & (tmp_time>>11);//高5位代表  时
    int min = 0x0000003f & (tmp_time>>5); //次6位代表  分
    int sec = 0x0000001f & tmp_time; //低5位代表  秒的1/2
    return QString::number(hour) + ":" + QString::number(min) + ":"+QString::number(sec*2 + msOffset);
}

QString DirectoryItemInfo::formatDate(short buff)
{
    short tmp_date = buff;
    int tmp_year = 0x0000007f & (tmp_date>>9);
    int tmp_mon = 0x0000000f & (tmp_date>>5);
    int tmp_day = 0x0000001f & (tmp_date);
    return QString::number(1980+tmp_year) + "年" + QString::number(tmp_mon) + "月"+QString::number(tmp_day)+ "日";
}

void DirectoryItemInfo::printStr()
{
    qDebug()<<"             文件信息";
    qDebug()<<"             文件名："<<fileName<<fileExtensionName<<"   文件属性:"<<getFileAtrrStr();
    qDebug()<<"             创建时间："<<fileCreate_date<<"  "<<"最近修改访问："<<fileAccess_date<<"    最近修改时间："<<fileLastRevise_date;

    unsigned int startClusterNum = fileStartClusterNum_H16*256 + fileStartClusterNum_L16;
    qDebug()<<"             文件开始簇号："<<startClusterNum;
    qDebug()<<"             文件大小："<<fileLength;

}

QString DirectoryItemInfo::getFileAtrrStr()
{
    int flag = 0x000000ff & fileAttr;

    switch (flag) {
    case 0:
        return "读写";
    case 1:
        return "只读";
    case 2:
        return "隐藏";
    case 4:
        return "系统";
    case 8:
        return "卷标";

    case 16:
        return "子目录";

    case 32:

        return "归档";

    default:
        break;
    }
}















