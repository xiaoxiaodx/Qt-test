#include "WidgetOSRItem.h"
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QPushButton>
#include "testchart.h"
WidgetOSRItem::WidgetOSRItem()
    :mOSRWidget(0)
{



    this->setAcceptHoverEvents(true);
    this->setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(ItemAcceptsInputMethod, true);
    setFlag(ItemIsFocusScope, true);
    setFlag(ItemHasContents, true);

}

void WidgetOSRItem::setOSRWidget(QVariant w)
{
    qDebug()<<"dsadasdsadsa";

    mOSRWidget = w.value<QWidget*>();
    if(mOSRWidget)
    {
        mOSRWidget->installEventFilter(this);
        this->update();
    }


    qDebug()<<"dsadasdsadsa11111";
}

void WidgetOSRItem::paint(QPainter *painter)
{
    painter->save();


    if(mOSRWidget == NULL)
    {
        painter->drawText(this->boundingRect(), Qt::AlignCenter, "painted item");
    }
    else
    {
        mOSRWidget->render(painter);
    }

    painter->restore();
}

bool WidgetOSRItem::eventFilter(QObject *obj, QEvent *e)
{
    bool res = QQuickPaintedItem::eventFilter(obj, e);
    if(obj == mOSRWidget)
    {
        switch(e->type())
        {
        case QEvent::Paint: //当OsrWidget paint的时候也触发自己paint
        {
            this->update();
        }
            break;
        }
    }

    return res;
}

void WidgetOSRItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickPaintedItem::geometryChanged(newGeometry, oldGeometry);

    if(mOSRWidget)
    {
        mOSRWidget->setGeometry(newGeometry.toRect());
    }
}

void WidgetOSRItem::hoverEnterEvent(QHoverEvent *e)
{
   if(!mOSRWidget)
       return;
   QEnterEvent enterEvent(e->posF(), mapToScene(e->posF()), QCursor::pos());//QEnterEvent(const QPointF & localPos, const QPointF & windowPos, const QPointF & screenPos)
   qApp->sendEvent(mOSRWidget, &enterEvent);
}

void WidgetOSRItem::hoverLeaveEvent(QHoverEvent *e)
{
    if(!mOSRWidget)
        return;
    qApp->sendEvent(mOSRWidget, e);
}

void WidgetOSRItem::hoverMoveEvent(QHoverEvent *e)
{
    if(!mOSRWidget)
        return;
    QMouseEvent me(QEvent::MouseMove, e->posF(), mapToScene(e->posF()), QCursor::pos(), Qt::NoButton, Qt::NoButton, 0);
    qApp->sendEvent(mOSRWidget, &me);
}

bool WidgetOSRItem::event(QEvent *e)
{
    if(!mOSRWidget)
    {
        e->ignore();
        return false;
    }

    switch(e->type())
    {
    case QEvent::HoverEnter:
    case QEvent::HoverLeave:
    case QEvent::HoverMove:
    {
        return QQuickPaintedItem::event(e);
    }
        break;
    default:
        return qApp->sendEvent(mOSRWidget, e);
    }
}
