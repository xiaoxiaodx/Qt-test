#ifndef PLAYAUDIO_H
#define PLAYAUDIO_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QDebug>
#include <QFile>


#include "mydevice.h"
class PlayAudio : public QObject
{
    Q_OBJECT
public:
    explicit PlayAudio(QObject *parent = nullptr);

    ~PlayAudio();
signals:

public slots:
    void slot_preparePlayAudio(int samplerate,int prenum,int bitwidth,int soundmode,long pts);
    void slot_playAudio();
    void preparePlayAudio(int sampleRate,int channelCount,int sampleSize);
    void slot_GetOneAudioFrame(unsigned char*buff,int len,long pts);
    void slot_audioStateChange(QAudio::State state);

    void slot_startAudio(bool start);
private:

    void initVariable();
    QAudioOutput *audioOutput;
    MyDevice *streamOut;

    QFile *audioFile;
    QByteArray *pcmBuffer;


    int abortDataLen;
    int audioCount;



};

#endif // PLAYAUDIO_H
