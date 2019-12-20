#ifndef FAT_FILEINFO_H
#define FAT_FILEINFO_H

#include "utils.h"
#include "dbr_info.h"
#include "fat_tableinfo.h"
#include "fat_dataarea.h"
class FAT_fileInfo//FAT 文件系统包括  --保留扇区--FAT1--FAT2--数据
{
public:
    FAT_fileInfo(HANDLE hfile,__int64 startNum);

    void parseDBRinfo();

    FAT_DataArea *dataArea;

private:
    DBR_info *dbrInfo;
    FAT_tableInfo *tableInfo1;
    FAT_tableInfo *tableInfo2;


    HANDLE m_hfile;
    __int64 m_startSectorNum;
};

#endif // FAT_FILEINFO_H
