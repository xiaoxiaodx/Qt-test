#include "mqtttest.h"

MqttTest::MqttTest(QObject *parent) : QObject(parent)
{

  m_client = new QMqttClient();

    connect(m_client,&QMqttClient::connected,this,&MqttTest::slot_conneted);
    connect(m_client,&QMqttClient::messageReceived,this,&MqttTest::slot_receMsg);

    if (m_client->state() == QMqttClient::Disconnected) {

        qDebug()<<"mqtt try to connted ";

           m_client->setHostname("10.67.3.58");
           m_client->setPort(1883);

           m_client->connectToHost();
       } else {//断开连接

           m_client->disconnectFromHost();
       }
}

void MqttTest::slot_conneted()
{

    qDebug()<<"mqtt slot_conneted ";

    //const QMqttTopicFilter &topic, const QMqttSubscriptionProperties &properties, quint8 qos
   QMqttTopicFilter topic;
   topic.setFilter("GZ-SERVER-001");
   m_client->subscribe(topic);
}

 void MqttTest::slot_receMsg(const QByteArray &message, const QMqttTopicName topic)
 {

     qDebug()<<"recMsg:"<<topic.name()<<QString(message);
 }
