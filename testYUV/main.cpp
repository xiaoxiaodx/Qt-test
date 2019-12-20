#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThread>
#include "videothreadrender.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    int execReturn = 0;

    {
        QQmlApplicationEngine engine;
        qmlRegisterType<VideoThreadRender>("SceneGraphRendering", 1, 0, "Renderer");
        engine.load(QUrl(QLatin1String("qrc:/main.qml")));
        if (engine.rootObjects().isEmpty())
            return -1;
        execReturn = app.exec();
    }

    for(QThread *t : qAsConst(VideoThreadRender::threads)){
        t->wait();
        delete t;
    }

    return execReturn;
}
