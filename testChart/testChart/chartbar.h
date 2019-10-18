#ifndef CHARTBAR_H
#define CHARTBAR_H

#include "chartbase.h"

class ChartBar : public ChartBase
{
public:
    ChartBar();

public slots:
    void slot_timeout_chartAnnimation();

private:
    void startChartAnimation(int ms);
    void drawChart(QPainter *painter);

private:

    QList<dataInfo> buff;
};

#endif // CHARTBAR_H
