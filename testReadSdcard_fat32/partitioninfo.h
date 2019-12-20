#ifndef PARTITIONINFO_H
#define PARTITIONINFO_H

#include "utils.h"
#include "fat_fileinfo.h"
class PartitionInfo
{
public:
    PartitionInfo(HANDLE hfile,__int64 startSectorNum);

    void printStr();
    void parse16byte();

    __int64 m_startSectorNum;
    HANDLE m_hfile;
    FAT_fileInfo *fatInfo;
    char bytes16[16];

    /***分区信息***/
    QString partitionStates;//分区状态
    int magneticHead ;//起始磁头
    int sectorStartPos;//起始扇区
    int cylinderStartPos;//起始柱号
    int partitionTypeInt;
    QString partitionType;//分区类型，（FAT32,扩展分区 等等）
    int magneticEnd ;//结束磁头
    int sectorEndPos ;//结束扇区
    int cylinderEndPos ;//结束柱面
    unsigned int  sectorOffset;//分区偏移的扇区数
    unsigned int sectorSum;//分区总扇区


    PartitionInfo *newPartition;//逻辑分区使用
    bool isNull;
    bool isExpansionPartition;
};

#endif // PARTITIONINFO_H
