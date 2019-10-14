
#include "QmlOSRExpMainWindow.h"
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QWindow>
#include <QDebug>
#include <QQuickItem>

QQmlEngine* QmlOSRExpMainWindow::gEngine = 0;
int QmlOSRExpMainWindow::gWindowCount = 0;

QmlOSRExpMainWindow::QmlOSRExpMainWindow(QWindow *parent)
    :QQuickWindow(parent)
    ,mComponent(0)
    ,mRootItem(0)
{
    checkInit();

    mComponent = new QQmlComponent(gEngine);
}

QmlOSRExpMainWindow::~QmlOSRExpMainWindow()
{
    checkUnInit();
}

void QmlOSRExpMainWindow::load(QUrl src)
{
    if(mRootItem)
    {
        qDebug() << "release root item:" << mRootItem;
        delete mRootItem;
        mRootItem = NULL;
    }

    mComponent->loadUrl(src);
    if(mComponent->isReady()) //注意，这里可能没准备好，需要巡回检测状态通过才能继续，本例就不提供这个操作了。
    {
        QObject* root = mComponent->create();


        QQuickItem* rootItem = qobject_cast<QQuickItem*>(root);
        if(rootItem)
        {
            rootItem->setParentItem(this->contentItem());
            mRootItem = rootItem;
        }
        else
        {
            qDebug() << "load error: dosen't suport " << root;
        }

    }
    else
    {
        qDebug() << "QmlComponent ERROR:" << mComponent->errorString();
    }
}

QQuickItem *QmlOSRExpMainWindow::rootItem()
{
    return mRootItem;
}

void QmlOSRExpMainWindow::checkInit()
{
    //_internal
    if(gWindowCount++ == 0)
    {
        qDebug() << "init qml engine";
        gEngine = new QQmlEngine;
    }
    //
}

void QmlOSRExpMainWindow::checkUnInit()
{
    //_internal
    if(--gWindowCount == 0)
    {
        qDebug() << "release qml engie";
        delete gEngine;
        gEngine = NULL;
    }
    //
}
