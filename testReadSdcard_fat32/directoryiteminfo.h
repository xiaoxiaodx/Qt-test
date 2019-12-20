#ifndef DIRECTORYITEMINFO_H
#define DIRECTORYITEMINFO_H

#include <QObject>

class DirectoryItemInfo
{


public:
    DirectoryItemInfo();

    enum FileType{
        End = 0,
        Delete,
        LongDirectory,
        ShortDirectory,
        ReadWrite,
        OnlyRead,
        Hide,
        System,
        Label,
        Subdirectory,
        Archive,
        Invalid
    };


    QString getFileAtrrStr( );
    int simpleParse(char *directoryItem,int &directirtNum,int &isLastDirectoy);//文件结束返回false;

    void printStr();


private:

    bool parseDirectoryItem_L(char *directoryItem,int count);//解析长文件名目录项，长度为36的倍数
    bool parseDirectoryItem_LSingle(char *directoryItem,int index);//解析长文件名目录项，长度为36
    bool parseDirectoryItem_S(char *directoryItem, int);//解析短文件名目录项,固定36个字节

    QString formatTime(short buff,int offset);
    QString formatDate(short buff);

    QString fileName;
    QString fileExtensionName;

    char fileAttr;
    QString fileAttrStr;
    QString fileCreate_ms;
    QString fileCreate_time;
    QString fileCreate_date;
    QString fileAccess_date;//文件最后访问日期

    unsigned short fileStartClusterNum_H16;
    QString fileLastRevise_time;
    QString fileLastRevise_date;
    unsigned short fileStartClusterNum_L16;
    unsigned int fileLength;

    bool isDelete;


};

#endif // DIRECTORYITEMINFO_H
