#ifndef MQTTTEST_H
#define MQTTTEST_H

#include <QObject>

#include <QDebug>

#include "QtMqtt/QMqttClient"

class MqttTest : public QObject
{
    Q_OBJECT
public:
    explicit MqttTest(QObject *parent = nullptr);

signals:

public slots:


    void slot_conneted();
    void slot_receMsg(const QByteArray &message, const QMqttTopicName topic);
private:



    QMqttClient *m_client;//mqtt client指针
};

#endif // MQTTTEST_H
