#include "fat_tableinfo.h"

FAT_tableInfo::FAT_tableInfo(HANDLE hfile,__int64 startNum,int sectorSize,int clusterSize)
{
    m_hfile = hfile;
    m_startSectorNum = startNum;
    m_sectorSize = sectorSize;
    m_clusterSize = clusterSize;//每簇扇区数
}



unsigned int FAT_tableInfo::getFileSize(unsigned int startClusterNum)
{
    QList<unsigned int> listCluster;
    listCluster.clear();
    getListCluster(listCluster,startClusterNum);

    return m_clusterSize*listCluster.size();


}

void FAT_tableInfo::getListCluster(QList<unsigned int> &listCluster,unsigned int ClusterNum)
{
    DWORD readlen = 4,readlenCash = 4;

    char clusterBytes[readlen];

    __int64 tmpClusterNum = 0x00000000ffffffff & ClusterNum;


    __int64 sectorSize = sectorSize;
    __int64 startByteNum = sectorSize * m_startSectorNum + tmpClusterNum*4;

    Utils::myFileSeek(m_hfile,startByteNum,FILE_BEGIN);

    ReadFile(m_hfile,clusterBytes,readlen,&readlenCash,NULL);


    int index = 0;
    unsigned int tableItemValue =  Utils::byte2Int(clusterBytes,4,index);

    if(0x0FFFFFF7 == tableItemValue)
        qDebug()<<"FAT表 intfo:"<<tableItemValue <<"号簇是坏簇";
    else if(0x0FFFFFFF == tableItemValue)
    {
        listCluster.append(tableItemValue);
        qDebug()<<"FAT表 intfo:"<<tableItemValue <<"号簇是结束";
    }
    else if(0 == tableItemValue)
    {
        qDebug()<<"FAT表 intfo:"<<tableItemValue <<"号簇空闲";
    }
    else if(0 == tableItemValue)
    {
        listCluster.append(tableItemValue);
        getListCluster(listCluster,tableItemValue);
    }

}
