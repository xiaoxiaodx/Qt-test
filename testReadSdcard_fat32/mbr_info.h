#ifndef MBR_INFO_H
#define MBR_INFO_H

#include <QObject>

#include "utils.h"
#include "partitioninfo.h"
#include <QList>
class MBR_info
{
public:
    MBR_info();

    void parseMBRsector(HANDLE hfile);
    void parseEBRsector(HANDLE hfile,__int64);
    QList<PartitionInfo*> listPartition;

protected:

    __int64 startSectorNum;
    HANDLE m_hfile;


//    PartitionInfo first_partition;
//    PartitionInfo second_partition;
//    PartitionInfo third_partition;
//    PartitionInfo forth_partition;

};

#endif // MBR_INFO_H
