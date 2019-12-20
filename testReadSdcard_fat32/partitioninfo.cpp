#include "partitioninfo.h"
#include <QDebug>

PartitionInfo::PartitionInfo(HANDLE hfile,__int64 startSectorNum)
{
    m_hfile = hfile;
    m_startSectorNum = startSectorNum;
    isNull = true;
    isExpansionPartition = false;
}

void PartitionInfo::parse16byte()
{
    char *parseBuff = bytes16;

    int index = 0;
    int ptsInt = 0x000000 & parseBuff[index++];

    if(ptsInt == 0)
        partitionStates = "非活动分区";
    else if(ptsInt == 0x80)
        partitionStates = "活动分区";
    else
        partitionStates = "无意义";

    magneticHead = 0x000000ff & parseBuff[index++];

    sectorStartPos = 0x0000003f & parseBuff[index];

    cylinderStartPos = (0x00000003 & (parseBuff[index++]>>6))*256 + 0x000000ff &parseBuff[index++];

    partitionTypeInt = 0x000000ff & parseBuff[index++];
    partitionType = QString::number(partitionTypeInt,16);

    magneticEnd = 0x000000ff & parseBuff[index++];

    sectorEndPos = 0x0000003f & parseBuff[index];
    cylinderEndPos = (0x00000003 & (parseBuff[index++]>>6))*256 + 0x000000ff &parseBuff[index++];


    sectorOffset = Utils::byte2Int(parseBuff,4,index);

    sectorSum = Utils::byte2Int(parseBuff,4,index);

    printStr();

    if(sectorOffset > 0 || sectorSum>0)
    {
        isNull = false;

        if(partitionTypeInt == 5)//扩展分区
        {
            isExpansionPartition = true;

        }
        else
        {
            __int64 tmpsectorOffset = 0x00000000ffffffff & sectorOffset;
            fatInfo = new FAT_fileInfo(m_hfile,m_startSectorNum+tmpsectorOffset);
            fatInfo->parseDBRinfo();
            isExpansionPartition = false;
        }

    }
    else
        isNull = true;


}

void PartitionInfo::printStr()
{

    qDebug()<<"分区信息: "+Utils::bytes2stringHex(bytes16,16);
    qDebug()<<"分区状态:"+partitionStates + "    系统文件标志（05是扩展分区,07是FAT32）："+ partitionType;
    qDebug()<<"起始磁头号："+QString::number(magneticHead) +"   起始扇区号:"+QString::number(sectorStartPos)+"   起始柱头号:"+QString::number(cylinderStartPos);
    qDebug()<<"结束磁头号："+QString::number(magneticEnd) +"   结束扇区号:"+QString::number(sectorEndPos)+"   结束柱头号:"+QString::number(cylinderEndPos);
    qDebug()<<"扇区偏移："+QString::number(sectorOffset) +"   分区大小（总扇区数）:"+QString::number(sectorSum)<<endl;

}
