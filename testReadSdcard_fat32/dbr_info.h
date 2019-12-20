#ifndef DBR_INFO_H
#define DBR_INFO_H

#include <QObject>
#include "utils.h"
class DBR_info
{
public:
    DBR_info(HANDLE handle,__int64 startPos);

    void parse512bytes(char *buff,int len);

    void printStr();



    int getSectorBytes() const;

    int getClusterSize() const;

    int getFatCounts() const;

    int getRemainSectorCounts() const;

    unsigned int getFatSectorCount1() const;

    unsigned int getStartClusterNum() const;

private:
    char byte512[512];
    HANDLE m_hfile;
    __int64 m_startSectorNum;//相对磁盘0位置的偏移


    /********************DBR 所有信息**********************/
    char jumpCommand[3];                        //跳转指令 3个字节
    char sysInfo[8];                            //系统标志和版本
    QString sysInfoStr;
    int sectorBytes;                 //每扇区字节数
    int clusterSize;                           //每簇扇区数
    int remainSectorCounts;          //保留扇区数
    int fatCounts;                             //FAT表个数
    int rootDirectory_maxCount;               //FAT32必须等于0，FAT12/FAT16为根目录中目录的个数；
    int sectorSum;                   //FAT32必须等于0，FAT12/FAT16为扇区总数。
    char StorageMedium;                         //哪种存储介质，0xF8标准值，可移动存储介质。
    int  fatSectorCount;             //FAT32必须为0，FAT12/FAT16为一个FAT 表所占的扇区数。
    int  trackSectorCount;           //每磁道扇区数，只对于“特殊形状”（由磁头和柱面分割为若干磁道）的存储介质有效，0x003F=63。
    int  trackSum;                   //磁头数，只对特殊的介质才有效，0x00FF=255。
    unsigned int hideSectorCount;               //EBR分区之前所隐藏的扇区数
    unsigned int fileSystemSectorSum;           //文件系统总扇区数
    unsigned int fatSectorCount1;               //每个FAT表占用扇区数

    char fat32Flag[2];                          //标记，此域FAT32 特有。
    char fat32Version[2];                       //FAT32版本号0.0，FAT32特有。
    unsigned int startClusterNum;               //根目录所在第一个簇的簇号，0x02
    int FSINFO;                      //FSINFO（文件系统信息扇区）扇区号0x01，该扇区为操作系统提供关于空簇总数及下一可用簇的信息。
    int backupLeadSector;                      //备份引导扇区的位置。备份引导扇区总是位于文件系统的6号扇区。
    char remainExtend[12];
    char a;
    char b;
    char extendLeadFlag;
    int volumeNumber;                           //卷序列号。通常为一个随机值。
    char volumeASSII[11];
    QString volumeStr;
    char filesystemASSII[8];
    QString filesystemASSIIstr;
    char leadCode[423];//保护引导代码和一些信息
    char endFlag[2];
};

#endif // DBR_INFO_H
