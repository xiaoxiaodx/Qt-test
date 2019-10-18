#include "barchart.h"

BarChart::BarChart()
{

    setAcceptedMouseButtons(Qt::LeftButton
                            | Qt::RightButton
                            | Qt::MiddleButton);
    setFlag(QQuickItem::ItemHasContents);

    isMousePress = false;


    connect(&axisAnimationTimer,&QTimer::timeout,this,&BarChart::slot_timeout_axisAnnimation);
    connect(&chartAnimationTimer,&QTimer::timeout,this,&BarChart::slot_timeout_chartAnnimation);
}


//在这里设置原点坐标是因为在构造函数没结束之前，控件的几何信息还未定
void BarChart::setCoordinateOriginX(float cx)
{

    m_coordinateOrigin.setX(cx);

}

void BarChart::setCoordinateOriginY(float cy)
{

    m_coordinateOrigin.setY(cy);

}

void BarChart::setUnitScale(float tx,float ty)
{
    XunitScale = tx;
    YunitScale = ty;
}

void BarChart::paint(QPainter *painter)
{

    painter->setRenderHint(QPainter::Antialiasing);

    drawAxis(painter);
    drawChart(painter);
}



void BarChart::drawAxis(QPainter *painter)
{

    painter->setPen(QPen(QBrush(Qt::black),1));

    //字体
    QFont newFont;
    newFont.setPixelSize(12);
    QFontMetrics fontMetrics(newFont);

    //坐标轴的终点位置，人的感官位置
    QPointF xAxisDesPt = QPointF(width() - XunitScale -m_coordinateOrigin.rx(),0);
    QPointF yAxisDesPt = QPointF(0,m_coordinateOrigin.ry() - YunitScale);

    //坐标轴的终点位置，像素位置
    QPointF xAxisDesPtPixPos = axisCoordinateTransformation(xAxisDesPt);
    QPointF yAxisDesPtPixPos = axisCoordinateTransformation(yAxisDesPt);

    float arrowOffset = 4;  //坐标轴箭头的偏移位置，控制箭头的大小
    //X轴
    painter->drawLine(m_coordinateOrigin,xAxisDesPtPixPos);
    painter->drawLine(axisCoordinateTransformation(QPointF(xAxisDesPt.rx()-arrowOffset,xAxisDesPt.ry()+arrowOffset)), xAxisDesPtPixPos);
    painter->drawLine(axisCoordinateTransformation(QPointF(xAxisDesPt.rx()-arrowOffset,xAxisDesPt.ry()-arrowOffset)), xAxisDesPtPixPos);

    //Y轴
    painter->drawLine(m_coordinateOrigin,yAxisDesPtPixPos);
    painter->drawLine(yAxisDesPtPixPos,axisCoordinateTransformation(QPointF(yAxisDesPt.rx()+arrowOffset,yAxisDesPt.ry()-arrowOffset)));
    painter->drawLine(yAxisDesPtPixPos,axisCoordinateTransformation(QPointF(yAxisDesPt.rx()-arrowOffset,yAxisDesPt.ry()-arrowOffset)));

    //轴上的刻度
    painter->setPen(QPen(QBrush(Qt::black),1));
    float scaleLength = 2;

    QRect boundingRect = fontMetrics.boundingRect(QString::number(0));
    painter->drawText(m_coordinateOrigin.rx() - boundingRect.width() ,
                      m_coordinateOrigin.ry() + boundingRect.height(),"O");


    int count = 1;


    for(float xCurPos = XunitScale ;xCurPos < xAxisDesPt.rx();xCurPos += XunitScale,count++){

        QPoint pt1(xCurPos,0);

        if(count % 10 == 0){

            QRect boundingRect = fontMetrics.boundingRect(QString::number(count));

            QPoint pt2(xCurPos,scaleLength*2);
            QPointF pixPoint1 = axisCoordinateTransformation(pt1);
            QPointF pixPoint2 = axisCoordinateTransformation(pt2);

            painter->drawText(pixPoint1.rx() - boundingRect.width() / 2,
                              pixPoint1.ry() +5+ boundingRect.height() / 2, QString::number(count));

            painter->drawLine(pixPoint1,pixPoint2);

        }else{
            QPoint pt2(xCurPos,scaleLength);
            painter->drawLine(axisCoordinateTransformation(pt1),axisCoordinateTransformation(pt2));
        }
    }

    count = 1;
    for(float yCurPos = YunitScale;yCurPos < yAxisDesPt.ry();yCurPos += YunitScale,count++){

        QPoint pt1(0,yCurPos);

        if(count %10 ==0){

            QRect boundingRect = fontMetrics.boundingRect(QString::number(count));

            QPoint pt2(scaleLength*2,yCurPos);

            QPointF pixPoint1 = axisCoordinateTransformation(pt1);
            QPointF pixPoint2 = axisCoordinateTransformation(pt2);

            painter->drawText(pixPoint1.rx() - boundingRect.width() -5,
                              pixPoint1.ry() + boundingRect.height() / 2, QString::number(count));

            painter->drawLine(pixPoint1,pixPoint2);

        }else {

            QPoint pt2(scaleLength,yCurPos);
            painter->drawLine(axisCoordinateTransformation(pt1),axisCoordinateTransformation(pt2));

        }
    }

}

void BarChart::drawChart(QPainter *painter)
{


    painter->setPen(QPen(QBrush(Qt::green),2));


    QPolygonF tmpPtF ;
    for(int i=0;i<polygon.size();i++){

        QPointF ptF = polygon.at(i);

        tmpPtF<< realCoordinateTransformation(ptF);

    }

    painter->drawPolyline(tmpPtF);
}


QPointF BarChart::axisCoordinateTransformation(QPointF realy)
{
    return  QPointF(m_coordinateOrigin.rx() + realy.rx(),m_coordinateOrigin.ry()-realy.ry());
}

QPointF BarChart::realCoordinateTransformation(QPointF realy)
{
    return axisCoordinateTransformation(QPointF(realy.rx()*XunitScale,realy.ry()*YunitScale));
}

void BarChart::slot_timeout_axisAnnimation()
{


    XunitScale += animationXRate;
    YunitScale += animationYRate;

    update();

    annimationCount --;
    if(annimationCount <= 1)
        axisAnimationTimer.stop();
}

void BarChart::slot_timeout_chartAnnimation()
{


    polygon.append(testpolygon.at(testpolygon.count() - annimationCount));

    update();

    annimationCount --;
    if(annimationCount <= 1)
        chartAnimationTimer.stop();
}

void BarChart::startAxisAnimation()
{
    annimationCount = 20;


    animationXRate = XunitScale / annimationCount;
    animationYRate = YunitScale / annimationCount;
    axisAnimationTimer.start(1000 / annimationCount);


    XunitScale = 0;
    YunitScale = 0;
}

void BarChart::startChartAnimation()
{


    polygon.clear();

    annimationCount = testpolygon.count();

    chartAnimationTimer.start(1000 / annimationCount);


}

void BarChart::mousePressEvent(QMouseEvent* event)
{


    if(event->button() == Qt::LeftButton){
        isMousePress = true;
        mouseDragPt.setX(event->x());
        mouseDragPt.setY(event->y());

    }else if(event->button() == Qt::RightButton){

        testpolygon<<(QPointF(10.4, 20.5)) << (QPointF(20.2, 30.2))
               <<(QPointF(30.4, 20.5))<< (QPointF(40.2, 30.2))
              <<(QPointF(50.4, 33.5))<< (QPointF(62, 5.2));

    }
}

void BarChart::mouseMoveEvent(QMouseEvent *event)
{

    if(isMousePress){

        float dx = event->x() - mouseDragPt.x();
        float dy = event->y() - mouseDragPt.y();


        m_coordinateOrigin.setX(m_coordinateOrigin.rx() + dx);
        m_coordinateOrigin.setY(m_coordinateOrigin.ry() + dy);


        mouseDragPt.setX(event->x());
        mouseDragPt.setY(event->y());

        update();
    }
}

void BarChart::mouseReleaseEvent(QMouseEvent *event)
{
    isMousePress = false;
}

void BarChart::wheelEvent(QWheelEvent *event)
{

    float de = 1.2;

    if(event->delta() > 0){

        XunitScale = XunitScale*de;
        YunitScale = YunitScale*de;

    }else {
        XunitScale = XunitScale/de;
        YunitScale = YunitScale/de;

    }
    update();

}

