#include "fat_fileinfo.h"

/*************************************************FAT文件系统分为************************
 *
MBR_info                                                   主引导(MBR)
                                                                |
                                                                |
                       _________________________________________|___________________________________
                      |                            |                          |                     |
PartitionInf        第一分区                      第二分区                    第三分区                第四分区        //主分区最多4个
                      |                            |                          |                     |
DBR_info             DBR                         ......                    ......                   |   （假设为引导分区）
                      |                  (非引导分区与第一分区一样)    (非引导分区与第一分区一样)            |
FAT_tableInfo        FAT1                                                                       EBR（扩展引导）
                      |                                                            _________________|______________
FAT_tableInfo        FAT2（有可能只有一个）                                          |                                |
                      |                                                          DBR                          EBR（扩展引导）
FAT_DataArea        数据区                                                         |                    ____________|___________
                                                                               ......                 |                        |
                                                                          (过程与第一分区的DBR一样)      DBR                   EBR（扩展引导）
                                                                                                                                |
                                                                                                                             .......
                                                                                                                          直到没有扩展引导项

注意：除了定位文件偏移（readfile）使用的单位是字节外，其余的都是以扇区为单位

*****************************************************************************************/

FAT_fileInfo::FAT_fileInfo(HANDLE hfile,__int64 startPos)
{
    m_hfile = hfile;
    m_startSectorNum = startPos;

}


void FAT_fileInfo::parseDBRinfo()
{
    DWORD readlen = 512,readlenCash = 512;

    char rectorBytes[readlen];

   // qDebug()<<"m_startSectorNum :"<<m_startSectorNum;
    __int64 sectorSize = 512;
    __int64 startByteNum = sectorSize * m_startSectorNum;
    Utils::myFileSeek(m_hfile,startByteNum,FILE_BEGIN);

    ReadFile(m_hfile,rectorBytes,readlen,&readlenCash,NULL);

    dbrInfo = new DBR_info(m_hfile,m_startSectorNum);//解析dbr
    dbrInfo->parse512bytes(rectorBytes,512);


    __int64 reaminSectorCount64 = 0x00000000ffffffff & dbrInfo->getRemainSectorCounts();
    __int64 FatSectorCount64 =  0x00000000ffffffff & dbrInfo->getFatSectorCount1();

    __int64 fat1StartPos = m_startSectorNum + reaminSectorCount64;
    tableInfo1 = new FAT_tableInfo(m_hfile,fat1StartPos,dbrInfo->getSectorBytes(),dbrInfo->getClusterSize());

    if(dbrInfo->getFatCounts() == 2)
    {
        __int64 fat2StartPos = m_startSectorNum +  reaminSectorCount64 +  0x00000000ffffffff & dbrInfo->getFatSectorCount1();
        tableInfo2 = new FAT_tableInfo(m_hfile,fat2StartPos,dbrInfo->getSectorBytes(),dbrInfo->getClusterSize());
    }


    __int64 dataAreaAreaOffsetBytes = m_startSectorNum + reaminSectorCount64 + FatSectorCount64*2;

    dataArea = new FAT_DataArea(m_hfile,dataAreaAreaOffsetBytes);

    dataArea->parseDataArea(dbrInfo->getClusterSize(),dbrInfo->getStartClusterNum());



}















