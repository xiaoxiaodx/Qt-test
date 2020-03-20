#include "playaudio.h"

PlayAudio::PlayAudio(QObject *parent) : QObject(parent)
{


    initVariable();
    //    audioFile = new QFile("playAudio.pcm");
    //    if (!audioFile->open(QIODevice::ReadOnly  |QIODevice::WriteOnly))
    //        return;


}


void PlayAudio::initVariable()
{

    pcmBuffer = new QByteArray;

    audioFile = nullptr;

    streamOut = nullptr;

    audioOutput = nullptr;

    abortDataLen = 100;

}

void PlayAudio:: slot_startAudio(bool start)
{
    if(start)
        audioOutput->start(streamOut);
    else
        audioOutput->stop();
}

void PlayAudio::slot_GetOneAudioFrame(unsigned char*buff,int len,long pts)
{


    //pcmBuffer->append((char*)buff,len);


//    if(audioOutput != nullptr && audioOutput->state() == QAudio::ActiveState){

//        pcmBuffer->append((char*)buff,len);

//    }

    if(abortDataLen > 0){
        abortDataLen--;
        return;
    }else if (abortDataLen == 0) {

            abortDataLen--;

            if(audioOutput != nullptr){
                audioOutput->start(streamOut);
                qDebug()<<"重新启动音频";
            }

    }else{
        if(audioOutput != nullptr && audioOutput->state() == QAudio::ActiveState){

            pcmBuffer->append((char*)buff,len);

        }
    }

}

void PlayAudio::slot_audioStateChange(QAudio::State state)
{

    if(state == QAudio::IdleState){
        pcmBuffer->clear();

        qDebug()<<"audioStateChange";
        abortDataLen = 10;

        //audioOutput->start(streamOut);
    }
}
void PlayAudio::slot_preparePlayAudio(int samplerate,int prenum,int bitwidth,int soundmode,long pts)
{
    preparePlayAudio(samplerate,1,16);
}

void PlayAudio::preparePlayAudio(int sampleRate,int channelCount,int sampleSize){

    qDebug()<<"preparePlayAudio thread:"<<QThread::currentThreadId();

    QAudioFormat audioFormat;

    //设置采样率
    audioFormat.setSampleRate(sampleRate);
    //设置通道数
    audioFormat.setChannelCount(channelCount);
    //设置采样大小，一般为8位或16位
    audioFormat.setSampleSize(sampleSize);
    //设置编码方式
    audioFormat.setCodec("audio/pcm");
    //设置字节序
    audioFormat.setByteOrder(QAudioFormat::LittleEndian);
    //设置样本数据类型
    audioFormat.setSampleType(QAudioFormat::SignedInt);
    //音频设备信息
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultOutputDevice();


    qDebug()<<"supportedCodecs:"<<info.supportedCodecs();
    if (!info.isFormatSupported(audioFormat)) {
        qDebug()<<"default format not supported try to use nearest";
        audioFormat = info.nearestFormat(audioFormat);
    }

    streamOut = new MyDevice(pcmBuffer);
    audioOutput = new QAudioOutput(audioFormat, this);

    connect(audioOutput,&QAudioOutput::stateChanged,this,&PlayAudio::slot_audioStateChange);
    //audioOutput->setBufferSize(3528 * 1000);
}


void PlayAudio::slot_playAudio(){

    // qDebug()<<"slot_playAudio thread thread:"<<QThread::currentThreadId();


    //    if(pcmBuffer.length() >= audioOutput->periodSize()){
    //        if(audioOutput&&audioOutput->state()!=QAudio::StoppedState&&
    //                audioOutput->state()!=QAudio::SuspendedState)
    //        {
    //            int chunks = audioOutput->bytesFree()/audioOutput->periodSize();
    //            //qDebug()<<"audioOutput->bytesFree() "<<audioOutput->bytesFree()<<"  "<<audioOutput->periodSize();

    //            for (int i=0;i<chunks;i++) {

    //                if (pcmBuffer.length() >= audioOutput->periodSize())
    //                {
    //                    //写入到扬声器

    //                    //qDebug()<<"bytesToWrite 1   "<<streamOut->bytesToWrite();
    //                    int writeLen = streamOut->writeData(pcmBuffer.data(),audioOutput->periodSize());
    //                    pcmBuffer.remove(0,writeLen);

    //                }
    //                else
    //                {
    //                    //写入到扬声器
    //                   // qDebug()<<"         写入到扬声器   "<<pcmBuffer.length()<<"        "<<chunks;

    //                    int len = pcmBuffer.length();
    //                    if(pcmBuffer.length() > 0){
    //                        //qDebug()<<"bytesToWrite 2   "<<streamOut->bytesToWrite();
    //                        int writeLen = streamOut->writeData(pcmBuffer.data(),len);

    //                        //emit signal_send(pcmBuffer.data(),len);
    //                        pcmBuffer.remove(0,writeLen);
    //                    }
    //                    break;
    //                }
    //            }
    //        }
    //    }
}




PlayAudio::~PlayAudio(){

    qDebug()<<"析构   PlayAudio";
    if(audioFile != nullptr){

        audioFile->close();

    }


    if(audioOutput != nullptr){
        audioOutput->deleteLater();

    }

    if(streamOut != nullptr){

        streamOut->close();
    }

    qDebug()<<"析构   PlayAudio 结束";

}
