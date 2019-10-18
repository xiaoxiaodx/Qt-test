#ifndef MQTTTEST_H
#define MQTTTEST_H

#include <QObject>

#include <QDebug>

#include "QtMqtt/QMqttClient"
#include "mqttpacket.h"

class MqttTest : public QObject
{
    Q_OBJECT
public:
    explicit MqttTest(QObject *parent = nullptr);

    Q_INVOKABLE void connectServer(QString ip,int port);
    Q_INVOKABLE void subscribeTopic(QString topic);
    Q_INVOKABLE void publishMsg(QString cmd,QVariant msgContent);

signals:

public slots:

    void slot_disConneted();
    void slot_conneted();
    void slot_receMsg(const QByteArray &message, const QMqttTopicName topic);
    void slot_createMqttConnect(QString ip,int port);
private:
    void consoleDebugStr(QString strContent,QString filename = "",QString funcName="", int lineCount=-1);
    void initVariant();

    QMqttClient *m_client;//mqtt client指针
    MqttPacket *m_mqttPacket;

    QString mainServerSubTopicName ;
    QString mainServerPubTopicName ;
};

#endif // MQTTTEST_H
