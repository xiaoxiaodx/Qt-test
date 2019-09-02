#ifndef CHILD1_H
#define CHILD1_H

#include "base.h"
class Child1 : public Base
{
    Q_OBJECT
public:
    explicit Child1();


public slots:
     void slot_test();
     void test();
};

#endif // CHILD1_H
