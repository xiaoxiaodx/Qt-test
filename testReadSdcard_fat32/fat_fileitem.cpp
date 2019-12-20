#include "fat_fileitem.h"
#include <QTextCodec>
Fat_fileItem::Fat_fileItem(HANDLE hfile,__int64 startNum,__int64 clusterSize,__int64 rootDirectoryNum)
{
    m_hfile = hfile;
    m_rootDirectorSectorNum = startNum;
    m_clusterSize = clusterSize;
    m_rootDirectoryNum = rootDirectoryNum;
    listFileItem.clear();


    fileName = "";
    fileExtensionName = "";

    fileAttr = 0;
    fileAttrStr = "";
    fileCreate_ms = "";
    fileCreate_time = "";
    fileCreate_date = "";
    fileAccess_date = "";//文件最后访问日期

    fileStartClusterNum_H16 = 0;
    fileLastRevise_time = "";
    fileLastRevise_date = "";
    fileStartClusterNum_L16 = 0;
    fileLength = 0;

    isDelete = false;
    isDirectory = false;
    isPreDirectory = false;
    isCurDirectory = false;
}
//递归将所有目录的字节数读到一个数组
bool Fat_fileItem::readSectorDirectoryItem(__int64 startBytesPos,QByteArray &arrDiretory)
{

    //int curLen = arrLen;
    int directoryArrFirstIndex = 0;

    DWORD readlen = 512,readlenCash = 512;
    char directorBytes[readlen];
    __int64 sectorSize = 512;
    __int64 startByteNum = sectorSize * startBytesPos;
    Utils::myFileSeek(m_hfile,startByteNum,FILE_BEGIN);

    int retrunPos = ReadFile(m_hfile,directorBytes,readlen,&readlenCash,NULL);

    //遍历所有目录项，如果目录项第一个字节为0，则证明目录项结束，
    //如果 needAddLen >512，所有该目录项在该扇区未结束，继续读下一扇区
    for(;directoryArrFirstIndex<sectorSize;directoryArrFirstIndex+=32)
        if(!directorBytes[directoryArrFirstIndex])
            break;

    int needAddLen = directoryArrFirstIndex;//需要的新增长度，就是目录字节数组第一项的下标（从0开始）
    if(needAddLen  == 0)
    {
        return false;
    }
    else
    {
        for(int i=0;i<needAddLen;i++)
            arrDiretory.append(directorBytes[i]);

        if(needAddLen >= 512)
            readSectorDirectoryItem(startBytesPos+1,arrDiretory);

        return true;
    }

}
//把目录项内容全部读进字节数组，然后在解析------ readfile 每次只能读512的倍数？，目录也属于文件
void Fat_fileItem::parseDirectory(__int64 startBytesPos)
{

    QByteArray dirctoryByteArr ;
    dirctoryByteArr.clear();


    readSectorDirectoryItem(startBytesPos,dirctoryByteArr);

    //qDebug()<<"***readSectorDirectoryItem:"<<Utils::bytes2stringHex(dirctoryByteArr.data(),dirctoryByteArr.size()) ;

    for(int i=0;i<dirctoryByteArr.size();)
    {
        int directorNum = 0;//长目录的顺序号，
        int isLastDirectoy = 0;
        int fileAttr =  simpleParse(dirctoryByteArr.data(),i,directorNum,isLastDirectoy);

        if(fileAttr == Delete )//往下一文件目录项遍历
        {
            i += 32;
            //qDebug()<<"文件删除";
            continue;
        }
        else if(fileAttr == Invalid)
        {
            i += 32;
            //qDebug()<<"文件不合法";
            continue;
        }
        else if(fileAttr == LongDirectory)
        {
            int bytesSize = directorNum * 32 + 32;//directorNum个长目录 + 一个短目录

            char *bytesArr = new char[bytesSize];

            for(int k=0;k<bytesSize;k++ )
                bytesArr[k] =  dirctoryByteArr.data()[i+k];

            Fat_fileItem *childFileItem = new Fat_fileItem(m_hfile,m_rootDirectorSectorNum,m_clusterSize,m_rootDirectoryNum);

            //qDebug()<<"long mu lu :"<<Utils::bytes2stringHex(bytesArr,bytesSize);
            parseDirectoryItem_L(bytesArr,bytesSize,childFileItem);

            childFileItem->parentClusterNum = this->fileStartClusterNum;
            childFileItem->parentDirectorOffsetBytes = i;

            childFileItem->infoByteArrLenInParent = bytesSize;

            for(int m=0;m<bytesSize;m++ )
                childFileItem->infoByteArrInParent.append(bytesArr[m]);

            listFileItem.append(childFileItem);

            int fileAttrInt = 0x000000ff & childFileItem->fileAttr;
            if(fileAttrInt == 0x10 )
            {

                if(childFileItem->isCurDirectory ||  childFileItem->isPreDirectory)
                    ;
                else
                {
                    __int64 tmp_startPos = this->m_rootDirectorSectorNum + (childFileItem->fileStartClusterNum-m_rootDirectoryNum) * m_clusterSize;
                    childFileItem->parseDirectory(tmp_startPos);
                }
            }


            delete bytesArr;
            bytesArr =  NULL;
            i += bytesSize;
        }
        else
        {

            Fat_fileItem *childFileItem = new Fat_fileItem(m_hfile,m_rootDirectorSectorNum,m_clusterSize,m_rootDirectoryNum);
            parseDirectoryItem_S(dirctoryByteArr.data(),i,childFileItem,false);

            childFileItem->parentClusterNum = this->fileStartClusterNum;
            childFileItem->parentDirectorOffsetBytes = i;


            childFileItem->infoByteArrLenInParent = 32;

            for(int m=0;m<32;m++)
                childFileItem->infoByteArrInParent.append(dirctoryByteArr.data()[i+m]);

            listFileItem.append(childFileItem);


            int fileAttrInt = 0x000000ff & childFileItem->fileAttr;
            if(fileAttrInt == 0x10)
            {


                if(childFileItem->isCurDirectory ||  childFileItem->isPreDirectory)
                    ;
                else
                {
                    __int64 tmp_startPos = this->m_rootDirectorSectorNum + (childFileItem->fileStartClusterNum-childFileItem->m_rootDirectoryNum) * m_clusterSize;
                    childFileItem->parseDirectory(tmp_startPos);
                }
            }
            i += 32;
        }

    }



}

void Fat_fileItem::parseDirectoryItem(QByteArray byteArr)
{

}

int Fat_fileItem::simpleParse(char *directoryItem,int startIndex,int &directirtNum,int &isLastDirectoy)
{

    int diyiwei = 0x000000ff & directoryItem[startIndex];


    if(diyiwei == 0)//文件目录结束
        return End;
    if(diyiwei == 0xe5)
        return Delete;

    char item = directoryItem[startIndex + 11];

    int di11wei = 0x000000ff & directoryItem[startIndex+ 11];

    switch(di11wei)
    {

    case 0x0f://长目录
    {
        int num = 0x1f & directoryItem[startIndex];
        isLastDirectoy = (item>>7) & 0x00000001;
        directirtNum = num;
        return LongDirectory;
    }
    case 0x00://读写
        return ReadWrite;
    case 0x01://只读
        return OnlyRead;
    case 0x02://隐藏
        return Hide;
    case 0x04://系统
        return System;
    case 0x08://卷标
        return Label;
    case 0x10://子目录
        isDirectory = true;
        return Subdirectory;
    case 0x20://归档
        return Archive;

    }
    return Invalid;


}

bool Fat_fileItem::parseDirectoryItem_L(char *directoryItem,int count,Fat_fileItem *child)//解析长文件名目录项
{
    int directorySize = count/32;

    //qDebug()<<"parseDirectoryItem_L:"<<Utils::bytes2stringHex(directoryItem,count) << " directorySize:"<<directorySize;

    for(int i=0;i<directorySize;i++)
    {
        if(i < directorySize-1)
            parseDirectoryItem_LSingle(directoryItem,i*32,child);
        else
            parseDirectoryItem_S(directoryItem,i*32,child,true);
    }

}

int Fat_fileItem::checkFileNameValidLen(char *buff,int buffLen)
{
    int validLen = 0;
    //qDebug()<<"checkFileNameValidLen            :"<<Utils::bytes2stringHex(buff,buffLen);
    for(int i=0;i<buffLen;i+=2)
    {
        int tmp1 = 0x000000ff & buff[i] ;
        int tmp2 = 0x000000ff & buff[i+1] ;
        if((tmp1 == 0 && tmp2==0) || (tmp1 == 0xff && tmp2==0xff))
        {
            return validLen;
        }else
            validLen += 2;
    }
    return validLen;
}

int Fat_fileItem::checkSpecialFileName(QString name)
{


    QString tmpName = name;
    tmpName.replace(" ","");

    int nameType = 0;
    if(tmpName.size() == 1 && tmpName.contains("."))
        nameType = 1;
    if(tmpName.size() == 2 && tmpName.contains(".."))
        nameType = 2;

    //qDebug()<< "    tmpName:"<<tmpName<<"1   name:"<<name<<"    len:"<<tmpName.size()<<" "<<tmpName.length()<<" "<<nameType;
    return nameType;
}


QString Fat_fileItem::byte2Unicode16(char *buff, int len )
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-16");

    int validLen = checkFileNameValidLen(buff,len);


    QByteArray arr;


    for(int i=0;i<validLen;i++)
        arr.append( buff[i]);

    QString validStr =  "";
    if(validLen>0)
        validStr = codec->toUnicode(arr);



    return validStr;

}

bool Fat_fileItem::parseDirectoryItem_LSingle(char *directoryItem ,int index1,Fat_fileItem *child)
{

    int index = index1;

    char ch1 = directoryItem[index++];
    //    bool isLastDirctory = (ch1>>7) & 0x01;

    //    int directirtNum = 0x0000001f & ch1;//已赋值

    QTextCodec *codec = QTextCodec::codecForName("UTF-16");

    char unicodeName1[10];
    QString unicodeName1Str = "";

    for(int i =0;i<10;i++)
        unicodeName1[i] = directoryItem[index++];
    unicodeName1Str = byte2Unicode16(unicodeName1,10);

    // qDebug()<<"unicodeName1 :"<<unicodeName1Str << " bytes:"<<Utils::bytes2stringHex(unicodeName1,10);

    int flag_longDir = 0x000000ff & directoryItem[index++];
    //    if(flag_longDir == 11)
    //        qDebug()<<"是长文件目录";
    //    else
    //        qDebug()<<"不是长文件目录";

    index ++ ;

    int checkValue = 0x000000ff & directoryItem[index++];//暂时没视野

    char unicodeName2[12];
    QString unicodeName2Str = "";
    for(int i =0;i<12;i++)
        unicodeName2[i] = directoryItem[index++];

    unicodeName2Str = byte2Unicode16(unicodeName2,12);

    //qDebug()<<"unicodeName2 :"<<unicodeName2Str<< " bytes:"<<Utils::bytes2stringHex(unicodeName2,12);


    int startCluster = 0x000000ff & directoryItem[index++] +  (0x000000ff & directoryItem[index++])*256;//置零

    char unicodeName3[4];
    QString unicodeName3Str = "";
    for(int i =0;i<4;i++)
        unicodeName3[i] = directoryItem[index++];

    unicodeName3Str = byte2Unicode16(unicodeName3,4);

    //qDebug()<<"unicodeName3 :"<<unicodeName3Str<< " bytes:"<<Utils::bytes2stringHex(unicodeName3,4);

    QString tmpFileName  = unicodeName1Str + unicodeName2Str + unicodeName3Str;

    child->fileName = tmpFileName + child->fileName;


}


//QString fileName;
//QString fileExtensionName;
//char fileAttr;
//QString fileCreate_ms;
//QString fileCreate_time;
//QString fileCreate_date;
//QString fileAccess_date;//文件最后访问日期
//unsigned short fileStartClusterNum_H16;
//QString fileLastRevise_time;
//QString fileLastRevise_date;
//unsigned short fileStartClusterNum_L16;
//unsigned short fileLength;
bool Fat_fileItem::parseDirectoryItem_S(char *directoryItem,int index1,Fat_fileItem *child,bool isLongDirectory)
{
    int index = index1;

    if(child == NULL)
        return false;

    QTextCodec* pCodec = QTextCodec::codecForName("gb2312");

    //调试
    QByteArray debugArr;
    for(int i=0;i<32;i++)
        debugArr.append(directoryItem[index1+i]);
    //qDebug()<<"parseDirectoryItem_S "<<Utils::bytes2stringHex(debugArr.data(),32) ;

    //name
    char tmpname[8] = {0};
    QByteArray arrFileName;
    for(int i=0;i<8;i++)
    {
        arrFileName.append(directoryItem[index]);
        tmpname[i] = directoryItem[index++];

    }

    int tmpType = 0;
    if(!isLongDirectory)
    {
        child->fileName = pCodec->toUnicode(arrFileName);

        tmpType = checkSpecialFileName(child->fileName);

        if(tmpType == 1)
            child->isCurDirectory = true;
        else if(tmpType == 2)
            child->isPreDirectory = true;
    }


   // qDebug()<< "************    "<<child->fileName <<"  "<<Utils::bytes2stringHex(tmpname,8)<<" "<<isLongDirectory  <<tmpType;
    //extension
    QByteArray arrExt;
    arrExt.clear();
    char tmpextensionName[3] = {0};
    for(int i=0;i<3;i++){
        arrExt.append(directoryItem[index]);
        tmpextensionName[i] = directoryItem[index++];

    }
    //qDebug()<<"tmpextensionName "<<Utils::bytes2stringHex(tmpextensionName,3) << QString::fromLocal8Bit(tmpextensionName);


    child->fileExtensionName =pCodec->toUnicode(arrExt);


    child->fileAttr = directoryItem[index++];
    index++;//系统保留

    short tmp_createms = 0x00ff & directoryItem[index++];
    child->fileCreate_ms = QString::number(tmp_createms*10%1000);

    short tmp_createtime = (0x00ff & directoryItem[index++]) + (0x00ff & directoryItem[index++])*256;
    child->fileCreate_time = formatTime(tmp_createtime,tmp_createms/100);

    short tmp_createdate = (0x00ff & directoryItem[index++]) + (0x00ff & directoryItem[index++])*256;
    child->fileCreate_date = formatDate(tmp_createdate);

    short tmp_accessDate = (0x00ff & directoryItem[index++]) + (0x00ff & directoryItem[index++])*256;
    child->fileAccess_date = formatDate(tmp_accessDate);

    child->fileStartClusterNum_H16 = (0x00ff & directoryItem[index++]) + (0x00ff & directoryItem[index++])*256;

    short tmp_lastReviseTime = (0x00ff & directoryItem[index++]) + (0x00ff & directoryItem[index++])*256;
    child->fileLastRevise_time = formatTime(tmp_lastReviseTime,0);

    short tmp_lastReviseData = (0x00ff & directoryItem[index++]) + (0x00ff & directoryItem[index++])*256;
    child->fileLastRevise_date = formatDate(tmp_lastReviseData);

    child->fileStartClusterNum_L16 = (0x000000ff & directoryItem[index++]) + (0x00ff & directoryItem[index++])*256;

    child->fileLength = (0x000000ff & directoryItem[index++]) + (0x000000ff & directoryItem[index++])*256 + (0x000000ff & directoryItem[index++])*256*256 + (0x000000ff & directoryItem[index++])*256*256*256;

    __int64 startClusterNumH = 0x00000000ffffffff & child->fileStartClusterNum_H16;
    __int64 startClusterNumL = 0x00000000ffffffff & child->fileStartClusterNum_L16;

    __int64 tmpvalue = 256;

    child->fileStartClusterNum = startClusterNumH*tmpvalue*tmpvalue + startClusterNumL;

    //qDebug()<< "************    startCluster:HL"<<startClusterNumH <<"  "<<startClusterNumL<<" "<<child->fileStartClusterNum <<"    **"<<sizeof(__int64);
    //child->printStr();
}

QString Fat_fileItem::formatTime(short buff,int msOffset)
{
    short tmp_time = buff;
    int hour = 0x0000001f & (tmp_time>>11);//高5位代表  时
    int min = 0x0000003f & (tmp_time>>5); //次6位代表  分
    int sec = 0x0000001f & tmp_time; //低5位代表  秒的1/2
    return QString::number(hour) + ":" + QString::number(min) + ":"+QString::number(sec*2 + msOffset);
}

QString Fat_fileItem::formatDate(short buff)
{
    short tmp_date = buff;
    int tmp_year = 0x0000007f & (tmp_date>>9);
    int tmp_mon = 0x0000000f & (tmp_date>>5);
    int tmp_day = 0x0000001f & (tmp_date);
    return QString::number(1980+tmp_year) + "年" + QString::number(tmp_mon) + "月"+QString::number(tmp_day)+ "日";
}

void Fat_fileItem::printStr()
{
    qDebug()<<"             文件信息" << "      根目录扇区："<<m_rootDirectorSectorNum <<"    父文件簇号："<<parentClusterNum;
    qDebug()<<"             文件名："<<fileName<<fileExtensionName<<"   文件属性:"<<getFileAtrrStr();
    qDebug()<<"             创建时间："<<fileCreate_date<<"  "<<"最近修改访问："<<fileAccess_date<<"    最近修改时间："<<fileLastRevise_date;
    qDebug()<<"             文件开始簇号："<<fileStartClusterNum <<"   根文件起始簇号："<<m_rootDirectorSectorNum<<"    簇大小："<<m_clusterSize;
    qDebug()<<"             文件大小："<<fileLength;
}



//End = 0,
//Delete,
//LongDirectory,
//ShortDirectory,
//ReadWrite,
//OnlyRead,
//Hide,
//System,
//Label,
//Subdirectory,
//Archive,
//Invalid,
int Fat_fileItem::getFileAtrrStr()
{
    int flag = 0x000000ff & fileAttr;

    switch (flag) {
    case 0:
        return ReadWrite;
    case 1:
        return OnlyRead;
    case 2:
        return Hide;
    case 4:
        return System;
    case 8:
        return Label;

    case 16:
        return Subdirectory;

    case 32:

        return Archive;

    default:
        break;
    }
}


