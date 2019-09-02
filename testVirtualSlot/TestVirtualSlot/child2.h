#ifndef CHILD2_H
#define CHILD2_H

#include "base.h"
class Child2 : public Base
{
    Q_OBJECT
public:
    explicit Child2();

signals:

public slots:
    void slot_test();
    void test();
};

#endif // CHILD2_H
