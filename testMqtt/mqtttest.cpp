#include "mqtttest.h"
#include <QDateTime>
#include <QJsonObject>
#include <QJsonDocument>

MqttTest::MqttTest(QObject *parent) : QObject(parent)
{

    initVariant();
}

void MqttTest::initVariant()
{
    m_client = nullptr;


    mainServerSubTopicName = "gzstreammedia/mainserver/winpc"+QString::number(QDateTime::currentSecsSinceEpoch(),10)+"/pullmsg";
    mainServerPubTopicName = "gzstreammedia/web/mainserver/pullmsg";

}

void MqttTest::slot_createMqttConnect(QString ip,int port)
{


    if(m_client == nullptr){
        m_client = new QMqttClient();
        m_mqttPacket = new MqttPacket;

        m_mqttPacket->setMainServerPubTopicName(mainServerPubTopicName);
        m_mqttPacket->setMainServerSubTopicName(mainServerSubTopicName);

        connect(m_client,&QMqttClient::connected,this,&MqttTest::slot_conneted);
        connect(m_client,&QMqttClient::disconnected,this,&MqttTest::slot_conneted);
        connect(m_client,&QMqttClient::messageReceived,this,&MqttTest::slot_receMsg);

        if (m_client->state() == QMqttClient::Disconnected) {

            qDebug()<<"mqtt try to connted ";

            m_client->setHostname(ip);
            m_client->setPort(port);

            m_client->connectToHost();
        } else {//断开连接

            m_client->disconnectFromHost();
        }
    }
}
void MqttTest::connectServer(QString ip,int port)
{

    slot_createMqttConnect(ip,port);

}

void MqttTest::subscribeTopic(QString topic)
{
//    QMqttTopicFilter topicF;
//    topicF.setFilter(mainServerSubTopicName);

    m_client->state();
    if(m_client != nullptr){

        consoleDebugStr("mqtt try to subscribe "+mainServerSubTopicName);
        auto subscription = m_client->subscribe(mainServerSubTopicName);
        if (!subscription) {


            consoleDebugStr("mqtt subscribe fail");
            return;
        }else
            consoleDebugStr("mqtt subscribe succ");
    }
}


void MqttTest::publishMsg(QString cmd,QVariant msgContent)
{


   QByteArray sendArr = m_mqttPacket->makePacket(cmd,msgContent);
   if (m_client->publish(mainServerPubTopicName, sendArr) == -1){

       consoleDebugStr("publish fail :");

   }else {
        consoleDebugStr("publish succ :   "+QString(sendArr));
    }

}

void MqttTest::slot_conneted()
{
    qDebug()<<"mqtt slot_conneted ";
}

void MqttTest::slot_disConneted()
{
    consoleDebugStr("Mqtt 断开连接");
}

void MqttTest::slot_receMsg(const QByteArray &message, const QMqttTopicName topic)
{


    qDebug()<<"unPacket  : "<<topic.name()<<"   "<<QString(message);

    QMap<QString,QVariant> map = m_mqttPacket->unPacket(topic.name(),message);





}

void MqttTest::consoleDebugStr(QString strContent,QString filename,QString funcName, int lineCount)
{

    qDebug()<<strContent;
}
