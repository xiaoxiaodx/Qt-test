#ifndef QMLOSREXPMAINWINDOW_H
#define QMLOSREXPMAINWINDOW_H


#include <QQuickWindow>
#include <QQmlComponent>

class QmlOSRExpMainWindow : public QQuickWindow
{
public:
    QmlOSRExpMainWindow(QWindow *parent = 0);
    ~QmlOSRExpMainWindow();

    void load(QUrl src);
    QQuickItem* rootItem();

private:
    static QQmlEngine* gEngine;
    static int gWindowCount;
    QQmlComponent* mComponent;
    QQuickItem* mRootItem;

    static void checkInit();
    static void checkUnInit();
};

#endif // QMLOSREXPMAINWINDOW_H
