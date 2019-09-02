#ifndef TEST_H
#define TEST_H

#include <QObject>
#include "base.h"
#include "child1.h"
#include "child2.h"
#include <QThread>
#include <QTimer>
class test : public QObject
{
    Q_OBJECT
public:
    explicit test(QObject *parent = nullptr);

signals:
   void signal_test();
public slots:
    void slot_timeout();

private:
    Child1 *child1;
    Child2 *child2;
    Base *base;
    QTimer *timer;
};

#endif // TEST_H
