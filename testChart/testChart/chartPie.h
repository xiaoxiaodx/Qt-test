#ifndef PIECHART_H
#define PIECHART_H

#include <QObject>
#include "chartbase.h"

class ChartPie : public ChartBase
{
public:
    ChartPie();


public slots:
    void slot_timeout_chartAnnimation();

private:
    void startChartAnimation(int ms);
    void drawChart(QPainter *painter);

private:

    QList<dataInfo> buff;
};

#endif // PIECHART_H
