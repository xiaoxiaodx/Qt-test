#ifndef SENDMSGQUEUE_H
#define SENDMSGQUEUE_H

#include <QObject>

class SendMsgQueue : public QObject
{
    Q_OBJECT
public:
    explicit SendMsgQueue(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SENDMSGQUEUE_H