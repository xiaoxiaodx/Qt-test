#include "mbr_info.h"
#include "windows.h"
MBR_info::MBR_info()
{
    LPCWSTR pStr= LPCWSTR(QString("\\\\.\\PhysicalDrive1").utf16());
    HANDLE hDevice =  CreateFile( pStr, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0 );

}


void MBR_info::parseMBRsector(HANDLE hfile)
{

    DWORD readlen = 512,readlenCash = 512;

    char rectorBytes[readlen];

    ReadFile(hfile,rectorBytes,readlen,&readlenCash,NULL);

    for(int i = readlen-66;i<readlen-2;i+=16)//最后66个字节表示 分区表信息 以及结束符 55 AA
    {

        PartitionInfo *pInfo = new PartitionInfo(hfile,0);

        for(int j=0;j<16;j++)
            pInfo->bytes16[j] = rectorBytes[i+j];

        pInfo->parse16byte();


        if(!pInfo->isNull)
        {
            if(pInfo->isExpansionPartition)
            {
                __int64 EBRSectorStart = 0x00000000ffffffff & pInfo->sectorOffset;

                parseEBRsector(hfile,EBRSectorStart);

            }
            else
                listPartition.append(pInfo);
        }

    }
}


//下一个EBR的位置等于   当前的分区扇区偏移（保留）+当前分区大小
//解析扩展分区使用
void MBR_info::parseEBRsector(HANDLE hfile,__int64 EBRSectorStart)
{
    qDebug()<<"EBRSectorStart   "<<EBRSectorStart;

    __int64 sectorBytes = 512;
    __int64 EBRSectorStart_bytes = EBRSectorStart * sectorBytes;

    Utils::myFileSeek(hfile,EBRSectorStart_bytes,FILE_BEGIN);

    DWORD readlen = 512,readlenCash = 512;

    char rectorBytes[readlen];

    ReadFile(hfile,rectorBytes,readlen,&readlenCash,NULL);

    PartitionInfo *pInfo = new PartitionInfo(hfile,EBRSectorStart);
    for(int j=0;j<16;j++)
        pInfo->bytes16[j] = rectorBytes[446+j];


    pInfo->parse16byte();

    if(!pInfo->isNull)
        listPartition.append(pInfo);

    PartitionInfo *pInfo1 = new PartitionInfo(hfile,0);
    for(int j=0;j<16;j++)
        pInfo1->bytes16[j] = rectorBytes[462+j];



    pInfo1->parse16byte();

    //    __int64 infoSize = 0x00000000ffffffff & pInfo1->sectorSum;
    //    pInfo1->m_startSectorNum = EBRSectorStart + infoSize;

    __int64 infoSize = 0x00000000ffffffff & pInfo->sectorSum;
    __int64 infoOffset = 0x00000000ffffffff & pInfo->sectorEndPos;
    pInfo1->m_startSectorNum = EBRSectorStart + infoSize + infoOffset;

    //qDebug()<<
    if(!pInfo1->isNull && pInfo1->isExpansionPartition)
    {


        parseEBRsector(hfile,pInfo1->m_startSectorNum);
    }


}





