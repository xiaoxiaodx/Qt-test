#ifndef DECODETHREAD_H
#define DECODETHREAD_H

#include <QThread>
class DecodeThread : public QThread
{
    Q_OBJECT
public:
    DecodeThread(QObject*parent = nullptr);
    void setUrl(QString);
    uchar* imgPtr{nullptr};
    uint videoW,videoH;

signals:
    void sigImage(uchar*,uint,uint);

protected:
    void run() override;

private:
    QByteArray arr;
    QString _url;
};

#endif // DECODETHREAD_H
