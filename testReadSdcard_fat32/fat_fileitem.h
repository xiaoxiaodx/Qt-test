#ifndef FAT_FILEITEM_H
#define FAT_FILEITEM_H

#include <QObject>
#include "utils.h"

class Fat_fileItem
{
public:
    Fat_fileItem(HANDLE hfile,__int64 startNum,__int64 clusterSize,__int64 rootDirectoryNum);
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
        Invalid,
    };


    int getFileAtrrStr( );

    void parseDirectory(__int64 startPos);
    bool readSectorDirectoryItem(__int64 startPos,QByteArray &arrDiretory);
    void parseDirectoryItem(QByteArray byteArr);
    int checkFileNameValidLen(char *,int);
    int checkSpecialFileName(QString);

    QString byte2Unicode16(char *,int);
    int simpleParse(char *directoryItem,int startIndex,int &directirtNum,int &isLastDirectoy);//文件结束返回false;




    void printStr();


    HANDLE m_hfile;
    QString m_FullName;
    __int64 m_rootDirectorSectorNum;//根目录所在扇区
    __int64 parentClusterNum;
    __int64 parentDirectorOffsetBytes;//在父目录中 自身信息相对父目录的起始的偏移字节

    __int64 m_clusterSize;
    __int64 m_rootDirectoryNum;
    QByteArray infoByteArrInParent;
    int infoByteArrLenInParent;


    QList<Fat_fileItem *> listFileItem;


    bool parseDirectoryItem_L(char *directoryItem,int count,Fat_fileItem *child);//解析长文件名目录项，长度为36的倍数
    bool parseDirectoryItem_LSingle(char *directoryItem,int index,Fat_fileItem *child);//解析长文件名目录项，长度为36
    bool parseDirectoryItem_S(char *directoryItem, int,Fat_fileItem *child,bool isLongDirectory);//解析短文件名目录项,固定36个字节

    QString formatTime(short buff,int offset);
    QString formatDate(short buff);

    QString fileName;
    QString fileExtensionName;

    char fileAttr;
    FileType fileAttrEnum;
    QString fileAttrStr;
    QString fileCreate_ms;
    QString fileCreate_time;
    QString fileCreate_date;
    QString fileAccess_date;//文件最后访问日期

    unsigned short fileStartClusterNum_H16;
    QString fileLastRevise_time;
    QString fileLastRevise_date;
    unsigned short fileStartClusterNum_L16;
    __int64 fileStartClusterNum;
    unsigned int fileLength;

    bool isDelete;
    bool isDirectory;//是否为目录（文件夹）
    bool isPreDirectory;//上级目录
    bool isCurDirectory;//当前目录
};

#endif // FAT_FILEITEM_H
