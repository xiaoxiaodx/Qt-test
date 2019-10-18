#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "barchart.h"


#include "chartpolyline.h"
#include "chartPie.h"
#include "chartbar.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<BarChart>("BarChart", 1, 0, "BarChart");

    qmlRegisterType<ChartBar>("ChartBar", 1, 0, "ChartBar");
    qmlRegisterType<ChartPie>("ChartPie", 1, 0, "ChartPie");
    qmlRegisterType<ChartPolyLine>("ChartPolyLine", 1, 0, "ChartPolyLine");

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
