#include "chartbar.h"

ChartBar::ChartBar()
{

}


void ChartBar::slot_timeout_chartAnnimation()
{
    int bufflen = buff.count();
    int testlen = testData.count();

    if(bufflen < testlen)
        buff.append(testData.at(bufflen));
    else
        chartAnimationTimer.stop();

    update();
}

void ChartBar::startChartAnimation(int ms)
{

    buff.clear();

    chartAnimationTimer.start(ms/testData.count());
}

void ChartBar::drawChart(QPainter *painter)
{

    for(int i=1;i<buff.size();i++){



        QPointF RectLeftBottom = realCoordinateTransformation(QPointF(buff.at(i-1).mPt.x(),0));
        QPointF RectRightTop = realCoordinateTransformation(buff.at(i).mPt);

        painter->setPen(QPen(QBrush(buff.at(i).mColor),2));

        //painter->drawLine(prePtf,curPtf);
        painter->fillRect(QRectF(RectLeftBottom,RectRightTop),QBrush(buff.at(i).mColor));

    }

}
