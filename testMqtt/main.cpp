#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mqtttest.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);




    qmlRegisterType<MqttTest>("MqttTest", 1, 0, "MqttTest");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
