#ifndef VIDEOTHREADRENDER_H
#define VIDEOTHREADRENDER_H
#include <QQuickItem>

QT_FORWARD_DECLARE_CLASS(RenderThread)
class VideoThreadRender : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString videoSource READ videoSource WRITE setVideoSource NOTIFY videoSourceChanged)
public:
    VideoThreadRender(QQuickItem *parent = nullptr);
    static QList<QThread*> threads;

public Q_SLOTS:
    void ready();

signals:
    void videoSourceChanged();

protected:
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

private:
    RenderThread *m_renderThread{nullptr};
    QString m_videoSource;

    void setVideoSource(QString);
    QString videoSource();
};

#endif // VIDEOTHREADRENDER_H
