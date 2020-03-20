#include "Mediabase.h"
#include <QPainter>
#include <QDebug>
#include <texturenode.h>

Mediabase::Mediabase()
{
    setFlag(QQuickItem::ItemHasContents);
    initVariable();

    createTcpThread();
    createPlayAudio();
    createAviRecord();
    //createWinTcpThread();

    QSize size;
    size.setWidth(640);
    size.setHeight(360);
    m_renderThread = new RenderThread(size,&listYuv,&yuvData,nullptr);



    qDebug()<<m_logIdentity;
    qDebug()<<"Mediabase thread:"<<QThread::currentThreadId()<< isRecord;


}

void Mediabase::initVariable()
{

    minBuffLen = 15;

    worker = nullptr;
    m_readThread = nullptr;

    winTcpWorker = nullptr;

    playAudio = nullptr;
    playAudioThread = nullptr;

    pffmpegCodec = nullptr;



    isImgUpdate  = false;
    isPlayAudio = false;
    isRecord =false;
    isScreenShot = false;
    isFirstData = false;


    isAudioFirstPlay = true;


    isStartRecord = false;

    mshotScreenFilePath = "";
    m_Img = new QImage();
    m_Img->fill(QColor("black"));
    preAudioTime = 0;
}



void Mediabase::createFFmpegDecodec()
{
    if(pffmpegCodec == nullptr)
    {
        pffmpegCodec = new FfmpegCodec;
        pffmpegCodec->vNakedStreamDecodeInit(AV_CODEC_ID_H264);
        pffmpegCodec->aNakedStreamDecodeInit(AV_CODEC_ID_PCM_ALAW,AV_SAMPLE_FMT_S16,8000,1);
        pffmpegCodec->resetSample(AV_CH_LAYOUT_MONO,AV_CH_LAYOUT_MONO,8000,44100,AV_SAMPLE_FMT_S16,AV_SAMPLE_FMT_S16,160);


        if(m_readThread != nullptr)
            connect(m_readThread,&QThread::finished,pffmpegCodec,&FfmpegCodec::deleteLater);
    }

}

void Mediabase::createMp4RecordThread()
{

}

void Mediabase::createAviRecord()
{

}

void Mediabase::createP2pThread()
{


}

void Mediabase::createWinTcpThread()
{

    winTcpWorker = new WinTcpThread;
    m_winSockThread = new QThread;
    winTcpWorker->moveToThread(m_winSockThread);

    connect(winTcpWorker,&WinTcpThread::signal_sendH264,this,&Mediabase::slot_recH264,Qt::DirectConnection);
    connect(winTcpWorker,&WinTcpThread::signal_sendPcmALaw,this,&Mediabase::slot_recPcmALaw,Qt::DirectConnection);
    connect(this,&Mediabase::signal_connentSer,winTcpWorker,&WinTcpThread::slot_createTcpConnect);
    m_winSockThread->start();
    //connect(this,&Mediabase::signal_tcpSendAuthentication,worker,&TcpWorker::slot_tcpRecAuthentication,Qt::DirectConnection);

}

void Mediabase::createTcpThread()
{

    worker = new TcpWorker(m_logIdentity.toString());
    m_readThread = new QThread();
    worker->moveToThread(m_readThread);

    connect(worker,&TcpWorker::signal_sendH264,this,&Mediabase::slot_recH264,Qt::DirectConnection);
    connect(worker,&TcpWorker::signal_sendPcmALaw,this,&Mediabase::slot_recPcmALaw);

    connect(worker,&TcpWorker::signal_waitTcpConnect,this,&Mediabase::slot_trasfer_waitingLoad);
    connect(worker,&TcpWorker::signal_endWait,this,&Mediabase::slot_trasfer_endLoad);

    connect(this,&Mediabase::signal_connentSer,worker,&TcpWorker::creatNewTcpConnect);
    connect(this,&Mediabase::signal_disconnentSer,worker,&TcpWorker::slot_disConnectSer);

    connect(this,&Mediabase::signal_tcpSendAuthentication,worker,&TcpWorker::slot_tcpRecAuthentication);
    connect(this,&Mediabase::signal_destoryTcpWork,worker,&TcpWorker::slot_destory,Qt::DirectConnection);

    connect(m_readThread,&QThread::finished,worker,&TcpWorker::deleteLater);
    connect(m_readThread,&QThread::finished,m_readThread,&QThread::deleteLater);

    m_readThread->start();
}


void Mediabase::creatDateProcessThread()
{


}

void Mediabase::createPlayAudio()
{
    playAudio = new PlayAudio;
    playAudioThread = new QThread;

    playAudio->moveToThread(playAudioThread);
    connect(this,&Mediabase::signal_playAudio,playAudio,&PlayAudio::slot_GetOneAudioFrame);
    connect(this,&Mediabase::signal_startAudio,playAudio,&PlayAudio::slot_startAudio);
    connect(this,&Mediabase::signal_preparePlayAudio,playAudio,&PlayAudio::slot_preparePlayAudio);
    connect(playAudioThread,&QThread::finished,playAudio,&PlayAudio::deleteLater);
    connect(playAudioThread,&QThread::finished,playAudioThread,&QThread::deleteLater);
    // connect(this,&Mediabase::signal_playAudio,playAudio,&PlayAudio::slot_playAudio);

    playAudioThread->start();



    playAudio = new PlayAudio;
    playAudioThread = new QThread;

}


void Mediabase::funPlayAudio(bool isPlay)
{

    if(playAudio != nullptr){


            isPlayAudio = !isPlayAudio;

            emit signal_startAudio(isPlayAudio);

        }
}

void Mediabase::funRecordVedio(bool isRecord)
{

    qDebug()<<"Mediabase 录像 thread:"<<QThread::currentThreadId()<< isRecord;

    this->isRecord = isRecord;

    if(this->isRecord){

        emit signal_startRecord(mDid,1000);

    }else{

        emit signal_endRecord();

    }
}

void Mediabase::funScreenShot()
{
    isScreenShot = true;
    if(m_Img != nullptr && (!m_Img->isNull())){

        QString filename;

         QDir dir;
        if(mshotScreenFilePath == ""){

           mshotScreenFilePath = dir.absolutePath() +"/ScreenShot";
        }
        QString desFileDir = mshotScreenFilePath +"/" +mDid;
        if (!dir.exists(desFileDir))
        {
            bool res = dir.mkpath(desFileDir);
            qDebug() << "新建最终目录是否成功:" << res;
        }


        QString curTimeStr = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
        QString tmpFileName = mDid+"_" + curTimeStr+".png";


        filename = desFileDir + "/"+tmpFileName;

        qDebug()<<" filename    "<<filename;

        if(m_Img->save(filename,0))
            qDebug()<<"图片保存成功";
        else
            qDebug()<<"图片保存失败";
    }
}


void Mediabase::slot_timeout()
{

}

void Mediabase::sendWaitLoad(bool &isWaiting)
{

    if(isWaiting)
        emit signal_endLoad();
    else
        emit signal_waitingLoad("loading");

    isWaiting = !isWaiting;
}

void Mediabase::slot_reconnectP2p()
{

}

void Mediabase::sendAuthentication(QString did,QString name,QString pwd)
{

    mDid = did;
    mAccount = name;
    mPassword = pwd;

    if(winTcpWorker != nullptr)
        winTcpWorker->tcpSendAuthentication(mDid,mAccount,mPassword);

    if(worker != nullptr)
        emit signal_tcpSendAuthentication(did,name,pwd);



    worker->testState();

    //worker->slot_tcpSendAuthentication(did,name,pwd);
}

void Mediabase::connectServer(QString ip, QString port)
{

   // timerUpdate.start(70);
    qDebug()<<" connectServer   ";

    if(worker != nullptr)
        worker->setLogIdetity(m_logIdentity.toString());

    emit signal_connentSer(ip,port.toInt());
}

void Mediabase::disConnectServer()
{


}



void Mediabase::ready()
{
    qDebug()<<"function ready";

    m_renderThread->surface = new QOffscreenSurface(); //实例一个离屏的Surface，有点像不显示的Window，使得opengl的contex能够绑定到它上面
    m_renderThread->surface->setFormat(m_renderThread->context->format());
    m_renderThread->surface->create(); //根据文档QOffscreenSurface的create只能在GUI线程调用，所以在这里做了实例和初始化。
    m_renderThread->moveToThread(m_renderThread); //移动到子线程循环
    //当场景失效后，关闭子线程的资源
    connect(window(), &QQuickWindow::sceneGraphInvalidated, m_renderThread, &RenderThread::shutDown, Qt::QueuedConnection);
    //启动子线程
    m_renderThread->start();
    update(); //再update一次用于实例TextureNode，因为程序刚初始化时会调用一次，但在初始化子线程后，返回了，所以要再来一次实例TextureNode。

}


//此函数是由渲染线程调用的，不是在GUI线程
QSGNode *Mediabase::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    TextureNode *node = static_cast<TextureNode *>(oldNode);
    qDebug()<<"updatePaintNode  currentThread:"<<QThread::currentThreadId();

    if (!m_renderThread->context) {
        QOpenGLContext *current = window()->openglContext();
        current->doneCurrent(); //取消opengl在当前上下文中的绑定，因为下面要设置shareContext，即将sharedContext移动到子线程
        m_renderThread->context = new QOpenGLContext();
        m_renderThread->context->setFormat(current->format());
        m_renderThread->context->setShareContext(current);
        m_renderThread->context->create();
        m_renderThread->context->moveToThread(m_renderThread); //context有线程归属性，一个context只能被它关联的线程调用makeCurrent，不能被其它线程调用;也只能有一个对应的surface
                                                               //一个线程在同一时刻也只能有一个context
        current->makeCurrent(window()); //恢复绑定
        qDebug()<<"invokeMethod ready";
        QMetaObject::invokeMethod(this, "ready"); //跨线程调用


        return 0;
    }

    if (!node) {
        node = new TextureNode(window()); //实例化自定义的纹理结点

        //当纹理在子线程渲染好后，将纹理id、大小设置到自定义的QSimpleTextureNode结构中
        connect(m_renderThread, &RenderThread::textureReady, node, &TextureNode::newTexture, Qt::DirectConnection);
        //update函数调用后，渲染线程会在适当的时候发出beforRendering信号
        connect(node, &TextureNode::pendingNewTexture, window(), &QQuickWindow::update, Qt::QueuedConnection);
        //在开始渲染之前，把子线程渲染好的纹理设置到QSimpletTextureNode中，以便渲染线程使用
        connect(window(), &QQuickWindow::beforeRendering, node, &TextureNode::prepareNode, Qt::DirectConnection);
        //渲染好的纹理被使用后，通知子线程渲染下一帧
        connect(node, &TextureNode::textureInUse, m_renderThread, &RenderThread::renderNext, Qt::QueuedConnection);

        // Get the production of FBO textures started..
        qDebug()<<"invokeMethod renderNext";
        QMetaObject::invokeMethod(m_renderThread, "renderNext", Qt::QueuedConnection);
    }

    qDebug()<<"*************1";
    node->setRect(boundingRect());//设置显示区域，为qml分配的整个区域
    return node;
}

//tcpworker 线程
void Mediabase::slot_recH264(char* h264Arr,int arrlen,quint64 time)
{


    createFFmpegDecodec();


   if(pffmpegCodec != nullptr){


//       if( listYuv.size() > 2){

//           delete listYuv.last().data;
//           listYuv.removeLast();
//       }else{
         pffmpegCodec->decodeVFrame((uchar*)h264Arr,arrlen,yuvData.data,yuvData.resolutionW,yuvData.resolutionH);
//           yuvInfo info;
//           info.data = nullptr;
//           pffmpegCodec->decodeVFrame((uchar*)h264Arr,arrlen,info.data,info.resolutionW,info.resolutionH);
//           if(info.data != nullptr)
//                listYuv.append(info);
       //}

   }
}


//tcpworker 线程
void Mediabase::slot_recPcmALaw( char * buff,int len,quint64 time)
{


    preAudioTime = time;
    createFFmpegDecodec();

   // emit signal_recordAudio(buff,len,time);


    //声卡准备
    if(isAudioFirstPlay){
        isAudioFirstPlay = false;
        emit signal_preparePlayAudio(44100,0,0,1,0);
        return;
    }else {
        if(pffmpegCodec != nullptr){
            QByteArray arr;
            pffmpegCodec->decodeAFrame((unsigned char*)buff,len,arr);

            if(isPlayAudio)
                emit signal_playAudio((unsigned char*)arr.data(),arr.length(),time);
        }
    }

}





void Mediabase::slot_trasfer_waitingLoad(QString str)
{
    emit signal_waitingLoad(str);
}

void Mediabase::slot_trasfer_endLoad()
{
    emit signal_endLoad();
}

void Mediabase::writeDebugfile(QString filenam,int lineCount,QString strContent)
{
    DebugLogFile::instance()->writeLog(m_logIdentity.toString(),filenam,QString::number(lineCount),strContent);
}

void Mediabase::funSetShotScrennFilePath(QString str)
{
    mshotScreenFilePath = str;
}
void Mediabase::funSetRecordingFilePath(QString str)
{
    emit signal_setRecordingFilePath(str);
}
Mediabase::~Mediabase()
{
    qDebug()<<mDid + " 析构   Mediabase";

    //析构tcpworker

    if(worker != nullptr)
    {
        emit signal_destoryTcpWork();
        worker->stopParsing();
        m_readThread->quit();
    }

    if(playAudioThread != nullptr)
        playAudioThread->quit();

    if(pffmpegCodec != nullptr)
        pffmpegCodec->deleteLater();


    qDebug()<<mDid + " 3333";

}

