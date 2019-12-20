#ifndef FAT_TABLEINFO_H
#define FAT_TABLEINFO_H

#include <QObject>
#include "utils.h"
#include <QList>
class FAT_tableInfo
{
public:
    FAT_tableInfo(HANDLE hfile,__int64 startNum,int sectorSize,int clusterSize);

    void searchClusterNum();

    unsigned int getFileSize(unsigned int startClusterNum);//返回簇个数

    void getListCluster(QList<unsigned int> &listCluster,unsigned int startClusterNum);//递归设置一个文件的簇链

private:

    HANDLE m_hfile;
    __int64 m_startSectorNum;
    int m_sectorSize;
    int m_clusterSize;
    //int m_
};

#endif // FAT_TABLEINFO_H
