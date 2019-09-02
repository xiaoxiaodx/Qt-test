#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QFile>
#include <QIODevice>

#include <QMessageBox>
#include <QDebug>

#include <windows.h>
#include "ccrashstack.h"

#include<QThread>
long __stdcall   callback(_EXCEPTION_POINTERS*   excp)

{

    CCrashStack crashStack(excp);

    QString sCrashInfo = crashStack.GetExceptionInfo();

    QString sFileName = "testcrash.log";



    QFile file(sFileName);

    if (file.open(QIODevice::WriteOnly|QIODevice::Truncate))

    {

        file.write(sCrashInfo.toUtf8());

        file.close();

    }



    qDebug()<<"Error:\n"<<sCrashInfo;

    //MessageBox(0,L"Error",L"error",MB_OK);

    QMessageBox msgBox;

    msgBox.setText(QString::fromUtf8("亲，我死了，重新启动下吧！"));

    msgBox.exec();



    return   EXCEPTION_EXECUTE_HANDLER;

}

int main(int argc, char *argv[])
{

    SetUnhandledExceptionFilter(callback);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    QThread *th;
    th->start();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
