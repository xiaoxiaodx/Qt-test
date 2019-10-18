#ifndef CHARTPOLYLINE_H
#define CHARTPOLYLINE_H

#include <QObject>
#include "chartbase.h"

class ChartPolyLine : public ChartBase
{
public:
    ChartPolyLine();

public slots:
    void slot_timeout_chartAnnimation();

private:
    void startChartAnimation(int ms);
    void drawChart(QPainter *painter);

private:

    QList<dataInfo> buff;

};

#endif // CHARTPOLYLINE_H
