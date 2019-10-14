
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QWindow>
#include <QDebug>
#include <QPushButton>



int main(int argc, char *argv[])
{
    //    QApplication app(argc, argv);
    //    QApplication::setAttribute(Qt::AA_UseSoftwareOpenGL, true);

    //    //register diy qml tools
    //  qmlRegisterType<WidgetOSRItem>("Diy.WidgetOSRItem",1,0, "WidgetOSRItem");

    //    QmlOSRExpMainWindow w;
    //    w.show();
    //    w.load(QUrl("qrc:/WidgetOSRExp.qml"));


    //    TestChart test;

    // w.rootItem()->setProperty("osrItem_OSRWidget", QVariant::fromValue(&test));


    //    QApplication app(argc, argv);
    //    QQmlApplicationEngine engine;


    //engine.load("qrc:/main.qml");

    //    engine.rootContext()->setContextProperty("osrItem_OSRWidget", QVariant::fromValue(&test));

    //    if (engine.rootObjects().isEmpty())
    //        return -1;



    QApplication app(argc, argv);

    //        QQmlApplicationEngine engine;
    //        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QApplication::setAttribute(Qt::AA_UseSoftwareOpenGL, true);

//    QQmlApplicationEngine* engine = new QQmlApplicationEngine;
//    QQmlComponent* component = new QQmlComponent(engine);


    QQmlEngine* engine = new QQmlEngine;
        QQmlComponent* component = new QQmlComponent(engine);


     qDebug()<<"11111111";
    component->loadUrl(QUrl(QStringLiteral("qrc:/main.qml")));
    if(component->isReady())
    {
         qDebug()<<"222222222222";
        //TODO: root 即为qml窗口
        QWindow* root = qobject_cast<QWindow*>(component->create());
        if(root)
        {

            qDebug()<<"333333";

            root->show();

            qDebug()<<"333333```````````````````";
            //TODO: 构造一个红色的pushButton嵌入root
            //** 这一步就是关键一步，要嵌入到QML窗口中的widgets都可以这样参考
            QPushButton* btn = new QPushButton();
            qDebug()<<"33333344444444444444";
            btn->setStyleSheet("background-color:red;");
            btn->setAttribute(Qt::WA_NativeWindow);

            if(!btn->windowHandle())
                btn->windowHandle()->create();
           btn->windowHandle()->setParent(root);

            qDebug()<<"333333898888888888888";

            btn->show();
        }
        else
        {
             qDebug()<<"4444444";
            qDebug() << component->errorString();
        }
    }
    else
    {
         qDebug()<<"5555555555";
        qDebug() << component->errorString();
    }

    qDebug()<<"6666666666";
    return app.exec();

}
