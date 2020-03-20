#ifndef ACTIVEX_H
#define ACTIVEX_H

#include <QWidget>
#include <QtCore>
#include <ActiveQt>


//# 设置内存执行编码 UTF-8
#ifdef Q_OS_WIN
#pragma execution_character_set("UTF-8")
#endif

// ObjectSafety
//# 控件安全标记类
#include <QAxAggregated>
#include <objsafe.h>
#include <QUuid>

class ObjectSafety : public QAxAggregated, public IObjectSafety
{
public:
    ObjectSafety(){
    }
    QAXAGG_IUNKNOWN;
    long queryInterface(const QUuid &iid, void **iface)
    {
        *iface = NULL;
        if (iid == IID_IObjectSafety)
        {
            *iface = (IObjectSafety*)this;
        }
        else
        {
            return E_NOINTERFACE;
        }
        AddRef();
        return S_OK;
    }
    HRESULT WINAPI GetInterfaceSafetyOptions(REFIID riid, DWORD *pdwSupportedOptions, DWORD *pdwEnabledOptions)
    {
        *pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA | INTERFACESAFE_FOR_UNTRUSTED_CALLER;
        *pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA | INTERFACESAFE_FOR_UNTRUSTED_CALLER;
        return S_OK;
    }
    HRESULT WINAPI SetInterfaceSafetyOptions(REFIID riid, DWORD pdwSupportedOptions, DWORD pdwEnabledOptions)
    {
        return S_OK;
    }
};
//End ObjectSafety

namespace Ui {
class ActiveX;
}

#include <Video/glyuvwidget.h>
class ActiveX : public QWidget,public QAxBindable
{
    Q_OBJECT
    Q_CLASSINFO("ClassID",     "{DF16845C-92CD-4AAB-A982-EB9840E74668}")
    Q_CLASSINFO("InterfaceID", "{616F620B-91C5-4410-A74E-6B81C76FFFE0}")
    Q_CLASSINFO("EventsID",    "{E1816BBA-BF5D-4A31-9855-D6BA432055FF}")
public:
    explicit ActiveX(QWidget *parent = 0);
    ~ActiveX();
public Q_SLOTS:
    QString Version();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ActiveX *ui;
    QAxAggregated* createAggregate()
    {
        return new ObjectSafety;
    }
    GLYuvWidget *w;
};

#endif // ACTIVEX_H
