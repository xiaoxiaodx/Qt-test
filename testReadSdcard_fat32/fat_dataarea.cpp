#include "fat_dataarea.h"

FAT_DataArea::FAT_DataArea(HANDLE hfile,__int64 startNum)
{
    m_hfile = hfile;
    m_startSectorNum = startNum;

}

void FAT_DataArea::parseDataArea(__int64 clusterSize,__int64 rootDirectorNum)
{

    rootDirector = new Fat_fileItem(m_hfile,m_startSectorNum,clusterSize,rootDirectorNum);

    rootDirector->parseDirectory(m_startSectorNum);


}


