#include "test.h"

test::test(QObject *parent) : QObject(parent)
{



    base = new Child1;
    timer = new QTimer;

    connect(this,SIGNAL(signal_test()),base,SLOT(slot_test()));
    connect(timer,SIGNAL(timeout()),this,SLOT(slot_timeout()));



    emit signal_test();

    base->test();
    timer->start(1000);
}



void test::slot_timeout()
{


    qDebug()<<"slot_timeout";
    QThread::msleep(2000);
    qDebug()<<"slot_timeout1";
}
