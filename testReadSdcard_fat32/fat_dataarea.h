#ifndef FAT_DATAAREA_H
#define FAT_DATAAREA_H

#include <QObject>
#include "utils.h"
#include "directoryiteminfo.h"
#include "fat_fileitem.h"
class FAT_DataArea
{
public:
    FAT_DataArea(HANDLE hfile,__int64 startNum);


    void parseDataArea(__int64 clusterSize,__int64 rootDirectorNum);



    Fat_fileItem *rootDirector;

private:
    __int64 RootDirectorySize;
    HANDLE m_hfile;
    __int64 m_startSectorNum;

    DirectoryItemInfo *directoryItemInfo;




    Fat_fileItem *curFileItem ;



};

#endif // FAT_DATAAREA_H
