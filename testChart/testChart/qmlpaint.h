#ifndef QMLPAINT_H
#define QMLPAINT_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QPainter>
#include "testchart.h"

class QmlPaint : public QQuickPaintedItem
{
    Q_OBJECT

public:
    QmlPaint();

protected:
    void paint(QPainter *painter);

private:
    TestChart test;
};

#endif // QMLPAINT_H
