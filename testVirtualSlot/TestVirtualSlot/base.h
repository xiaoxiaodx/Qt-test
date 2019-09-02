#ifndef BASE_H
#define BASE_H

#include <QObject>
#include <QDebug>
class Base : public QObject
{
    Q_OBJECT
public:
    explicit Base(QObject *parent = nullptr);

    virtual void test();
signals:

public slots:
    virtual void slot_test();

};

#endif // BASE_H
