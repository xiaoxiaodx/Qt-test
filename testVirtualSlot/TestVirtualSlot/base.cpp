#include "base.h"

Base::Base(QObject *parent) : QObject(parent)
{

}

void Base::slot_test()
{

    qDebug()<<"slot_test Base";
}

void Base::test()
{
    qDebug()<<"test Base";

}
