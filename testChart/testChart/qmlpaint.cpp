#include "qmlpaint.h"

QmlPaint::QmlPaint()
{

    test.show();
}


void QmlPaint::paint(QPainter *painter)
{


    QPen pen(Qt::red, 10);
    QLinearGradient gradient;
    gradient.setStart(0, 50);
    gradient.setFinalStop(200, 50);
    gradient.setColorAt(0, Qt::blue);
    gradient.setColorAt(0.2, Qt::green);
    gradient.setColorAt(0.4, Qt::red);
    gradient.setColorAt(0.6, Qt::yellow);
    gradient.setColorAt(1, Qt::cyan);
    painter->setPen(pen);
    painter->setBrush(gradient);
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->drawLine(0,0,100,100);
}
