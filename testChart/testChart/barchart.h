#ifndef BARCHART_H
#define BARCHART_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QPainter>
#include <QPointF>
#include <QDebug>
#include <QPolygon>
class BarChart : public QQuickPaintedItem
{
    Q_OBJECT
public:
    BarChart();

    Q_INVOKABLE void setCoordinateOriginX(float cx);
    Q_INVOKABLE void setCoordinateOriginY(float cy);
    Q_INVOKABLE void setUnitScale(float tx,float ty);

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
};

#endif // BARCHART_H
