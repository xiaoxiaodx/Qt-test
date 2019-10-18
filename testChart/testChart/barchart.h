#ifndef BARCHART_H
#define BARCHART_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QPainter>
#include <QPointF>
#include <QDebug>
#include <QPolygon>
#include <QTimer>
class BarChart : public QQuickPaintedItem
{
    Q_OBJECT
public:
    BarChart();

    Q_INVOKABLE void setCoordinateOriginX(float cx);
    Q_INVOKABLE void setCoordinateOriginY(float cy);
    Q_INVOKABLE void setUnitScale(float tx,float ty);

    Q_INVOKABLE void startAxisAnimation();
    Q_INVOKABLE void startChartAnimation();

public slots:
    void slot_timeout_axisAnnimation();
    void slot_timeout_chartAnnimation();
protected:
    void paint(QPainter *painter);
    void mousePressEvent(QMouseEvent* event);

     void mouseMoveEvent(QMouseEvent *event);
     void mouseReleaseEvent(QMouseEvent *event);
     void wheelEvent(QWheelEvent *event);

private:
    void drawAxis(QPainter *painter);
    void drawChart(QPainter *painter);

    QPointF axisCoordinateTransformation(QPointF realY);
    QPointF realCoordinateTransformation(QPointF realY);


    QPointF m_coordinateOrigin;//原点
    float XunitScale;//X轴的单位长度：每一个单位使用几个像素
    float YunitScale;//Y轴的单位长度：每一个单位使用几个像素

    bool isMousePress;
    QPointF mouseDragPt;



    QPolygonF polygon;
    QPolygonF testpolygon;

    //图表动画

    //轴动画
    int annimationCount;//每秒变化的次数
    float animationXRate;
    float animationYRate;
    QTimer axisAnimationTimer;
    QTimer chartAnimationTimer;
};

#endif // BARCHART_H
