#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mytreemodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

     qmlRegisterType<MyTreeModel>("MyTreeModel", 1, 0, "MyTreeModel" );

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
