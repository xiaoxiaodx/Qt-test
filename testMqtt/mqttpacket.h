#ifndef MQTTPACKET_H
#define MQTTPACKET_H

#include <QObject>
#include <QMap>
#include <QVariant>

class MqttPacket : public QObject
{
    Q_OBJECT
public:
    explicit MqttPacket();


    void setMainServerSubTopicName(QString str);
    void setMainServerPubTopicName(QString str);
    QByteArray makePacket(QString cmd,QVariant msgContent);
    QMap<QString,QVariant> unPacket(QString topic,QByteArray arr);
signals:

public slots:

private:
    void unPacketGetDevicelist(QMap<QString,QVariant> &map,QJsonDocument &jsDoc);
    void unPacketGetserverlist(QMap<QString,QVariant> &map,QJsonDocument &jsDoc);


    QString mainServerSubTopicName;//与主服务器通信订阅的主题
    QString mainServerPubTopicName;//与主服务器通信发布的主题

    QString sessionid;

    QMap<QString,int> mapMsgCount;
};

#endif // MQTTPACKET_H
