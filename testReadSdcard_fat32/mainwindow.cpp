#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include <QMap>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    mbr = new MBR_info();
    ui->treeWidget->setColumnCount(1); //设置列数
    ui->treeWidget->setHeaderLabel(tr("文件浏览")); //设置头的标题

    //    QTreeWidgetItem *imageItem1 = new QTreeWidgetItem(ui->treeWidget,QStringList(QString("图像1")));
    //    imageItem1->setIcon(0,QIcon("xxx.png"));
    //    QTreeWidgetItem *imageItem1_1 = new QTreeWidgetItem(imageItem1,QStringList(QString("Band1"))); //子节点1
    //    imageItem1->addChild(imageItem1_1); //添加子节点

    //    QTreeWidgetItem *imageItem2 = new QTreeWidgetItem(ui->treeWidget,QStringList(QString("图像2")));
    //    QTreeWidgetItem *imageItem2_1 = new QTreeWidgetItem(imageItem2,QStringList(QString("Band1"))); //子节点1
    //    QTreeWidgetItem *imageItem2_2 = new QTreeWidgetItem(imageItem2,QStringList(QString("Band2"))); //子节点2
    //    imageItem2->addChild(imageItem2_1);  //添加子节点
    //    imageItem2->addChild(imageItem2_2);

    //    QTreeWidgetItem *imageItem2_11 = new QTreeWidgetItem(imageItem2_1,QStringList(QString("Band1"))); //子节点11
    //    imageItem2_1->addChild(imageItem2_11);

    //    ui->treeWidget->expandAll(); //结点全部展开

    LPCWSTR pStr= LPCWSTR(QString("\\\\.\\PhysicalDrive1").utf16());
    HANDLE hDevice =  CreateFile( pStr, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0 );

    mbr->parseMBRsector(hDevice);

    connect(ui->treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(OnTreeItemDoubleClick(QTreeWidgetItem*,int)));
    connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(OnTreeItemClick(QTreeWidgetItem*,int)));
    addPartitionView();

}

void MainWindow::addPartitionView()
{
    //qDebug()<<"listPartition.size():"<<mbr->listPartition.size();

    for(int i=0;i<mbr->listPartition.size();i++)
    {

        QTreeWidgetItem *imagePartition = new QTreeWidgetItem(ui->treeWidget,QStringList(QString("分区")+QString::number(i)));
        imagePartition->setIcon(0,QIcon(":/img/partition.png"));

        imagePartition->setData(0, Qt::UserRole, 0);


        QVariantMap map;
        map.insert("fileType",0);
        map.insert("partitionNum",i);
        map.insert("pos",mbr->listPartition.at(i)->sectorOffset);
        imagePartition->setData(0, Qt::UserRole, map);


        PartitionInfo *partion = mbr->listPartition.at(i);
        Fat_fileItem *rootDirector = partion->fatInfo->dataArea->rootDirector;

        //qDebug()<<"sectorOffset:"<<rootDirector->listFileItem.size();


        addFileView(imagePartition,rootDirector);

    }


}

void MainWindow::addFileView(QTreeWidgetItem *parent,Fat_fileItem *fileinfo)
{
    if(fileinfo == NULL)
        return;
    QList<Fat_fileItem*> listFile = fileinfo->listFileItem;
    for(int i=0;i<listFile.size();i++)
    {
        Fat_fileItem *tmpfileinfo = listFile.at(i);
        if( (!tmpfileinfo->isCurDirectory) &&  (!tmpfileinfo->isPreDirectory))
        {

            QString fullName = tmpfileinfo->fileName;
            QTreeWidgetItem *imageItem = new QTreeWidgetItem(parent,QStringList(fullName)); //子节点1


            if(tmpfileinfo->getFileAtrrStr() == tmpfileinfo->Subdirectory)
                imageItem->setIcon(0,QIcon(":/img/file.png"));
            else if(fullName.contains(".txt") || fullName.contains(".TXT"))
                imageItem->setIcon(0,QIcon(":/img/text.png"));
            else if(fullName.contains(".avi") || fullName.contains(".AVI"))
                imageItem->setIcon(0,QIcon(":/img/video.png"));

            parent->addChild(imageItem); //添加子节点

            QVariantMap vMap ;

            vMap.insert("pos",tmpfileinfo->m_rootDirectorSectorNum);
            vMap.insert("clusterNum",tmpfileinfo->fileStartClusterNum);
            vMap.insert("parentClusterNum",tmpfileinfo->parentClusterNum);
            vMap.insert("bytesArrStart",tmpfileinfo->parentDirectorOffsetBytes);
            vMap.insert("bytesArr",tmpfileinfo->infoByteArrInParent);
            vMap.insert("bytesLen",tmpfileinfo->infoByteArrLenInParent);

            imageItem->setData(0, Qt::UserRole, vMap);
            addFileView(imageItem,tmpfileinfo);
        }




    }
}

void MainWindow::OnTreeItemDoubleClick(QTreeWidgetItem *item, int num)
{



}

void MainWindow::OnTreeItemClick(QTreeWidgetItem *item, int num)
{
    QVariantMap vMap = item->data(0,Qt::UserRole).toMap();

    __int64 pos = vMap.value("pos").toLongLong();
    __int64 clusterNum = vMap.value("clusterNum").toLongLong();
    __int64 parentClusterNum = vMap.value("parentClusterNum").toLongLong();
    __int64 bytesArrStart = vMap.value("bytesArrStart").toLongLong();
    int bytesLen = vMap.value("bytesLen").toInt();
    QByteArray bytesArr = vMap.value("bytesArr").toByteArray();

    qDebug()<<"file Info :（根目录所在簇为2号簇，以下提到的簇号是相对0号簇的偏移）";
    qDebug()<<"        根目录扇区数:"<<pos <<"  文件所在簇号"<<clusterNum;
    qDebug()<<"        父文件所在簇号:"<<parentClusterNum <<"  所在父目录的起始字节位置"<<bytesArrStart;
    qDebug()<<"        字节长度:"<<bytesLen <<"  字节数组"<<Utils::bytes2stringHex(bytesArr.data(),bytesLen);


}

MainWindow::~MainWindow()
{
    delete ui;
}
