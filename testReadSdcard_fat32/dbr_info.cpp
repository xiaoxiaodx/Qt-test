#include "dbr_info.h"

DBR_info::DBR_info(HANDLE handle,__int64 startPos)
{
    m_hfile = handle;
    m_startSectorNum = startPos;
}

void DBR_info::parse512bytes(char * buff,int len)
{

    //    【1】0x00~0x02：3 个字节，跳转指令。
    int index =0;
    jumpCommand[0] = buff[index++];//3 个字节，跳转指令。
    jumpCommand[1] = buff[index++];
    jumpCommand[2] = buff[index++];
    //    【2】0x03~0x0A：8 个字节，文件系统标志和版本号，这里为 MSDOC5.0。
    for(int i=0;i<8;i++)//8 个字节，文件系统标志和版本号，这里为 MSDOC5.0。
    {
        sysInfo[i] = buff[index];
        sysInfoStr.append(buff[index++]);
    }
    //    【3】0x0B~0x0C：2 个字节，每扇区字节数，512（0X02 00）。
    sectorBytes = Utils::byte2Int(buff,2,index);//0x000000ff & buff[index++] + (0x000000ff & buff[index++])*256;

    //    【4】0x0D~0x0D：1 个字节，每簇扇区数，8（0x08）。
    clusterSize = 0x000000ff & buff[index++];       //1 个字节，每簇扇区数，8（0x08）。

    //    【5】0x0E~0x0F：2 个字节，保留扇区数，2272（0x08 E0）。 加上256（MBR分区）=2528。FAT分区表从逻辑地址2528扇区开始
    remainSectorCounts = Utils::byte2Int(buff,2,index);;

    //    【6】0x10~0x10：1 个字节，FAT 表个数，2。
    fatCounts = 0x000000ff & buff[index++];

    //    【7】0x11~0x12：2 个字节，根目录最多可容纳的目录项数，FAT12/16 通常为 512。FAT32 不使用此处值，置 0。
    rootDirectory_maxCount = Utils::byte2Int(buff,2,index);;

    //    【8】0x13~0x14：2 个字节，扇区总数，小于 32MB 时使用该处存放。超过 32MB 时使用偏移 0x20~0x23 字节处的 4 字节存放。笔者的 SD 卡容量为 2GB，所以不使用该处，置 0.
    sectorSum = Utils::byte2Int(buff,2,index);;

    //    【9】0x15~0x15：1 个字节，介质描述符，0xF8 表示本地硬盘。
    StorageMedium =  buff[index++];

    //    【10】0x16~0x17：2 个字节，每个 FAT 表的大小扇区数（FAT12/16 使用，FAT32 不使用此处，置 0）。
    fatSectorCount = Utils::byte2Int(buff,2,index);;

    //    【11】0x18~0x19：2 个字节，每磁道扇区数，63（0x00 3F）。
    trackSectorCount = Utils::byte2Int(buff,2,index);;

    //    【12】0x1A~0x1B：2 个字节磁头数，255（0x00 FF）。
    trackSum = Utils::byte2Int(buff,2,index);;

    //    【13】0x1C~0x1F：4 个字节，分区前已使用扇区数，63（0x00 00 00 3F）。EBR分区之前所隐藏的扇区数,保留区，数据地址要加上这个。
    hideSectorCount = Utils::byte2uInt(buff,4,index);

    //    【14】0x20~0x23：4 个字节，文件系统总扇区数，15646657（0x 00 EEBF C1）。
    fileSystemSectorSum =  Utils::byte2uInt(buff,4,index);

    //    【15】0x24~0x27：4 个字节，每个 FAT 表的大小扇区数，15248（0x 00 00 3B 90）。
    fatSectorCount1 = Utils::byte2uInt(buff,4,index);

    //    【16】0x28~0x29：2 个字节，标记。
    for(int i=0;i<2;i++)
        fat32Flag[i] = buff[index++];

    //    【17】0x2A~0x2B：2 个字节，版本号。
    for(int i=0;i<2;i++)
        fat32Version[i] = buff[index++];


    //    【18】0x2C~0x2F：4 个字节，根目录簇号，2。（虽然在 FAT32 文件系统下，根目录可以存放在数据区的任何位置，但是通常情况下还是起始于 2 号簇）
    startClusterNum = Utils::byte2uInt(buff,4,index);

    //    【19】0x30~0x31：2 个字节，FSINFO（文件系统信息扇区）扇区号，1。（上图的标注即用黄色条纹的标注有误，请读者注意）该扇区为操作系统提供关于空簇总数及下一可用簇的信息。
    FSINFO = Utils::byte2uInt(buff,2,index);

    //    【20】0x32~0x33：2 个字节，备份引导扇区的位置，6。（上图的标注即用黄色条纹的标注有误，请读者注意）备份引导扇区总是位于文件系统的 6 号扇区。
    backupLeadSector = Utils::byte2uInt(buff,2,index);

    //    【21】0x34~0x3F：12 个字节，未使用。
    index += 12;

    //    【22】0x40~0x40：1 个字节，BIOS INT 13H 设备号，0x80。（BISO驱动器号）
    index++;

    //    【23】0x41~0x41：1 个字节，未用。
    index++;

    //    【24】0x42~0x42：1 个字节，扩展引导标志。0x29。
    extendLeadFlag = buff[index++];

    //    【25】0x43~0x46：1 个字节，卷序列号。通常为一个随机值。
    volumeNumber = 0x000000ff & buff[index++];

    //    【26】0x47~0x51：11 个字节，卷标（ASCII 码），如果建立文件系统的时候指定了卷标，会保存在此。笔者当时没有指定卷表，上图中的 YCY 是后来指定的。
    for(int i=0;i<11;i++)
    {
        volumeStr.append(index);
        volumeASSII[i] = buff[index++];
     }

    //    【27】0x52~0x59：8 个字节，文件系统格式的 ASCII 码，FAT32。
    for(int i=0;i<8;i++)
    {
        filesystemASSIIstr.append(buff[index]);
        filesystemASSII[i] = buff[index++];

    }

    //    【28】0x5A~0x1FD：410 个字节，未使用。该部分没有明确的用途。
    for(int i=0;i<423;i++)
        leadCode[i] = buff[index++];

    //    【29】0x1FE~0x1FF：签名标志“55 AA”
    for(int i=0;i<2;i++)
        endFlag[i] = buff[index++];



    printStr();



}


void DBR_info::printStr()
{
    qDebug()<<"***DBR info*** (当前位置："+QString::number(m_startSectorNum)+")";
    qDebug()<<"         文件系统标志和版本号"+sysInfoStr<<"    卷标："<<filesystemASSIIstr+"    文件格式:"+filesystemASSIIstr;
    qDebug()<<"         总扇区数："+QString::number(fileSystemSectorSum)+"     FAT扇区数:"+QString::number(fatSectorCount1) + "     保留扇区数："+QString::number(remainSectorCounts);
    qDebug()<<"         每扇区字节数："+QString::number(sectorBytes)+"     每簇扇区数"+QString::number(clusterSize) ;
    qDebug()<<"         FAT表个数："+QString::number(fatCounts)+"       根目录最多扇区数"+QString::number(rootDirectory_maxCount) + "   扇区总数："+QString::number(sectorSum);
    qDebug()<<"         FAT表扇区数："+QString::number(fatSectorCount)+"     磁道扇区数"+QString::number(trackSectorCount) + "    根目录簇号："+QString::number(startClusterNum);
    qDebug()<<"         引导标志:"+QString::number(0x000000ff &extendLeadFlag,16) +"    结束标志："+Utils::bytes2stringHex(endFlag,2)<<endl;
}

int DBR_info::getSectorBytes() const
{
    return sectorBytes;
}

int DBR_info::getClusterSize() const
{
    return clusterSize;
}

int DBR_info::getFatCounts() const
{
    return fatCounts;
}

int DBR_info::getRemainSectorCounts() const
{
    return remainSectorCounts;
}

unsigned int DBR_info::getFatSectorCount1() const
{
    return fatSectorCount1;
}

unsigned int DBR_info::getStartClusterNum() const
{
    return startClusterNum;
}

