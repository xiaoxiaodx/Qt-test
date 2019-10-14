#ifndef TESTCHART_H
#define TESTCHART_H


#include <QtCharts/QChartView>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts>
#include <QWindow>

class TestChart : public QMainWindow
{
    Q_OBJECT
public:
    explicit TestChart(QMainWindow *parent = nullptr);

signals:

public slots:

private:
    QLineSeries *series;
    QChart *chart ;
    QValueAxis *axisX;
    QLogValueAxis *axisY;
};

#endif // TESTCHART_H
