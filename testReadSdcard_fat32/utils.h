#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <windows.h>
#include <QDebug>

class Utils : public QObject
{
    Q_OBJECT

public:
    static QString bytes2stringHex(char *buff,int len)
    {
        QString str = "";
        for(int i=0;i<len;i++)
        {
            int tmpChar = 0x000000ff & buff[i];
            str = str + QString::number(tmpChar,16) + " ";
        }

        return str;
    }


     static __int64 myFileSeek (HANDLE hf, __int64 distance, DWORD MoveMethod)//定位扇区
     {
         LARGE_INTEGER li;


         li.QuadPart = distance;

         li.LowPart = SetFilePointer (hf,li.LowPart,&li.HighPart,MoveMethod);

         if (li.LowPart == INVALID_SET_FILE_POINTER && GetLastError()!= NO_ERROR)
         {

             li.QuadPart = -1;

         }
         return li.QuadPart;

     }


     static int byte2Int(char *buff,int byteCount ,int &index)//len 代表几个字节
     {
         int value = 0;

         for(int i=0;i<byteCount;i++)
         {
             int tmpValue = 0x000000ff & buff[index++];

             int beishu = 1;
             for(int j=0;j<i;j++)
             {
                 beishu = beishu*256;
             }

             value += tmpValue * beishu;


         }

         return value;
     }

     static unsigned int byte2uInt(char *buff,int byteCount,int &index)
     {
         unsigned int value = 0;
         for(int i=0;i<byteCount;i++)
         {
             unsigned int tmpValue = 0x000000ff & buff[index++];

             unsigned int beishu = 1;
             for(int j=0;j<i;j++)
             {
                 beishu = beishu*256;
             }

             value += tmpValue * beishu;
         }
         return value;
     }
};

#endif // UTILS_H
