/*              图表基类
 * 描述：自定义绘制图表的基类（折线图，饼图，条形图）
 *
 * 功能：1、图表之外的一切绘制，包括背景绘制，坐标轴的绘制(子类提供具体的图表绘制)
 *      2、坐标变换（将显示的坐标转换为屏幕像素坐标）,坐标自由伸缩，平移
 *      3、轴的尺寸动画
 *
 * 作者：DMJ
 *
*/

#include "chartbase.h"


ChartBase::ChartBase()
{

    setAcceptedMouseButtons(Qt::LeftButton
                            | Qt::RightButton
                            | Qt::MiddleButton);
    setFlag(QQuickItem::ItemHasContents);

    isMousePress = false;



    connect(&axisAnimationTimer,&QTimer::timeout,this,&ChartBase::slot_timeout_axisAnnimation);
    connect(&chartAnimationTimer,&QTimer::timeout,this,&ChartBase::slot_timeout_chartAnnimation);

}



//在这里设置原点坐标是因为在构造函数没结束之前，控件的几何信息还未定
void ChartBase::setCoordinateOriginX(float cx)
{

    m_coordinateOrigin.setX(cx);

}

void ChartBase::setCoordinateOriginY(float cy)
{

    m_coordinateOrigin.setY(cy);

}

void ChartBase::setUnitScale(float tx,float ty)
{
    XunitScale = tx;
    YunitScale = ty;
}

void ChartBase::paint(QPainter *painter)
{

    painter->setRenderHint(QPainter::Antialiasing);

    drawAxis(painter);
    drawChart(painter);
}



void ChartBase::drawAxis(QPainter *painter)
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

    painter->setBackground(QBrush(Qt::blue));

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

QPointF ChartBase::axisCoordinateTransformation(QPointF realy)
{
    return  QPointF(m_coordinateOrigin.rx() + realy.rx(),m_coordinateOrigin.ry()-realy.ry());
}

QPointF ChartBase::realCoordinateTransformation(QPointF realy)
{
    return axisCoordinateTransformation(QPointF(realy.rx()*XunitScale,realy.ry()*YunitScale));
}

void ChartBase::slot_timeout_axisAnnimation()
{


    XunitScale += animationXRate;
    YunitScale += animationYRate;

    update();

    annimationCount --;
    if(annimationCount <= 1)
        axisAnimationTimer.stop();
}

/*
 * 动画的思路是将 XunitScale，YunitScale 大小从0恢复原来的大小，
 * 每个时钟周期恢复animationXRate，animationYRate 个大小
 *

*/
void ChartBase::startAxisAnimation(int ms)
{

    annimationCount = 20;

    animationXRate = XunitScale / annimationCount;
    animationYRate = YunitScale / annimationCount;
    axisAnimationTimer.start(ms / annimationCount);


    XunitScale = 0;
    YunitScale = 0;
}


void ChartBase::mousePressEvent(QMouseEvent* event)
{


    if(event->button() == Qt::LeftButton){
        isMousePress = true;
        mouseDragPt.setX(event->x());
        mouseDragPt.setY(event->y());

    }else if(event->button() == Qt::RightButton){

        testData.append(dataInfo(QPointF(10.4, 20.5),Qt::red));
        testData.append(dataInfo(QPointF(20.2, 30.2),Qt::yellow));
        testData.append(dataInfo(QPointF(30.4, 20.5),Qt::green));
        testData.append(dataInfo(QPointF(50.4, 33.5),Qt::blue));
        testData.append(dataInfo(QPointF(70.4, 5.5),Qt::cyan));


    }
}

void ChartBase::mouseMoveEvent(QMouseEvent *event)
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

void ChartBase::mouseReleaseEvent(QMouseEvent *event)
{
    isMousePress = false;
}

void ChartBase::wheelEvent(QWheelEvent *event)
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
//空函数，由子类实现
void ChartBase::slot_timeout_chartAnnimation(){}

void ChartBase::drawChart(QPainter *painter){}

void ChartBase::startChartAnimation(int ms){
    qDebug()<<"ChartPolyLine::startChartAnimation";
}
