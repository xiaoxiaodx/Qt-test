#include "mqttpacket.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include <QDebug>
MqttPacket::MqttPacket()
{

    mainServerSubTopicName = "";
    mainServerPubTopicName = "";
    sessionid = "";

    mapMsgCount.clear();
}

void MqttPacket::setMainServerSubTopicName(QString str)
{
    mainServerSubTopicName = str;
}
void MqttPacket::setMainServerPubTopicName(QString str)
{
    mainServerPubTopicName = str;
}


QByteArray MqttPacket::makePacket(QString cmd,QVariant msgContent)
{

    QJsonObject jObject;

    if(cmd.compare("loginmainserver")==0){

        QJsonObject jObjectData ;
        jObjectData.insert("username",msgContent.toMap().value("username").toString());

        jObjectData.insert("password",msgContent.toMap().value("password").toString());
        jObject.insert("data",jObjectData);
    }else if(cmd.compare("modifyusrpasswd")==0){

        QJsonObject jObjectData ;
        jObjectData.insert("username",msgContent.toMap().value("username").toString());
        jObjectData.insert("oldpassword",msgContent.toMap().value("oldpassword").toString());
        jObjectData.insert("newpassword",msgContent.toMap().value("newpassword").toString());
        jObject.insert("data",jObjectData);

    }else if(cmd.compare("getdevicelist")==0){

        QJsonObject jObjectData ;
        QString did = msgContent.toMap().value("deviceid").toString();
        if(did.compare("")!=0)
            jObjectData.insert("deviceid",did);

        jObject.insert("data",jObjectData);
    }else if(cmd.compare("getserverlist")==0){

        //不需要做额外添加
    }

    int msgCount = 0;
    //对消息进行计数，每组一次包则加1，收到回应则减1
    if(mapMsgCount.contains(cmd)){
        msgCount = mapMsgCount.value(cmd);
        mapMsgCount.insert(cmd,msgCount+1);
    }else
        mapMsgCount.insert(cmd,msgCount);

    jObject.insert("cmd",cmd);
    jObject.insert("method","request");
    jObject.insert("srctopic",mainServerSubTopicName);
    jObject.insert("desttopic",mainServerPubTopicName);
    jObject.insert("sessionid",sessionid);
    jObject.insert("msgid",QString::number(msgCount));
    QJsonDocument jsDoc(jObject);


    return jsDoc.toJson();
}

QMap<QString,QVariant> MqttPacket::unPacket(QString topic,QByteArray arr)
{


    QMap<QString,QVariant> map;

    QJsonDocument jsDoc = QJsonDocument::fromJson(arr);

    QString cmd =  jsDoc.object().value("cmd").toString();

    map.insert("cmd",cmd);


    if(cmd.compare("loginmainserver")==0){
        QJsonObject jObjectData = jsDoc.object().value("data").toObject();
        map.insert("statuscode",jsDoc.object().value("statuscode").toString());
        map.insert("msgid",jsDoc.object().value("msgid").toString());

        sessionid = jObjectData.value("sessionid").toString();
        map.insert("sessionid",sessionid);

    }else if(cmd.compare("modifyusrpasswd")==0){


        map.insert("statuscode",jsDoc.object().value("statuscode").toString());
        map.insert("msgid",jsDoc.object().value("msgid").toString());

    }else if(cmd.compare("getdevicelist")==0){

        unPacketGetDevicelist(map,jsDoc);

    }else if(cmd.compare("getserverlist")==0){

        unPacketGetserverlist(map,jsDoc);
    }

    return map;
}


void MqttPacket::unPacketGetDevicelist(QMap<QString,QVariant> &map,QJsonDocument &jsDoc)
{

    map.insert("statuscode",jsDoc.object().value("statuscode").toString());

    QJsonArray jarr = jsDoc.object().value("data").toObject().value("devicelist").toArray();


    QVariantList mapDeviceList;

    for (int i=0;i<jarr.size();i++) {

        QJsonValue jvalue = jarr.at(i);


        QVariantMap deviceInfo;
        deviceInfo.insert("deviceid",jvalue.toObject().value("deviceid").toString());
        deviceInfo.insert("mediatoken",jvalue.toObject().value("mediatoken").toString());
        deviceInfo.insert("state",jvalue.toObject().value("state").toString());

        mapDeviceList.append(deviceInfo);
    }

    map.insert("devicelist",mapDeviceList);
}

void MqttPacket::unPacketGetserverlist(QMap<QString,QVariant> &map,QJsonDocument &jsDoc)
{

    map.insert("statuscode",jsDoc.object().value("statuscode").toString());

    QJsonArray jarr = jsDoc.object().value("data").toObject().value("streammedialist").toArray();


    QVariantList mapServiceList;

    for (int i=0;i<jarr.size();i++) {

        QJsonValue jvalue = jarr.at(i);


        QVariantMap mediaSerInfo;
        mediaSerInfo.insert("mediatoken",jvalue.toObject().value("mediatoken").toString());
        mediaSerInfo.insert("name",jvalue.toObject().value("name").toString());
        mediaSerInfo.insert("location",jvalue.toObject().value("location").toString());
        mediaSerInfo.insert("onlinestate",jvalue.toObject().value("onlinestate").toString());

        mapServiceList.append(mediaSerInfo);
    }

    map.insert("serverlist",mapServiceList);
}

