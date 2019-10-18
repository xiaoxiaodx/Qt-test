import QtQuick 2.12
import QtQuick.Window 2.12
import MqttTest 1.0
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")



    Button{

        id:btnConnectSer
        text:"connect"


        onClicked: {

            mqtttest.connectServer("10.67.1.167",1883);

        }
    }

    Button{

        id:btnConnectSer1
        text:"subscribe main"
        anchors.left: btnConnectSer.right
        anchors.leftMargin: 10
        onClicked: {

            mqtttest.subscribeTopic("");

        }
    }

    Button{

        id:subscribe2
        text:"subscribe ci"
        anchors.left: btnConnectSer1.right
        anchors.leftMargin: 10
        onClicked: {

            mqtttest.subscribeTopic("");

        }
    }

    Button{

        id:btnConnectSer2
        text:"loginmainserver"


        anchors.left: btnConnectSer.left
        anchors.top: btnConnectSer.bottom
        anchors.topMargin: 10
        onClicked: {


            var data={ "username":"admin","password":"admin"};

            mqtttest.publishMsg("loginmainserver",data);

        }
    }

    Button{

        id:btnConnectSer3
        anchors.left: btnConnectSer2.right
        anchors.leftMargin: 10
        anchors.top: btnConnectSer2.top
        text:"modifyusrpasswd"
        onClicked: {

            var data={ "username":"admin","oldpassword":"admin","newpassword":"newpassword"};

            mqtttest.publishMsg("modifyusrpasswd",data);

        }
    }

    Button{

        id:btnConnectSer5


        anchors.left: btnConnectSer3.right
        anchors.top: btnConnectSer3.top
        anchors.leftMargin: 10

        text:"getdevicelist"
        onClicked: {

            var data={ "deviceid":""};

            mqtttest.publishMsg("getdevicelist",data);

        }
    }

    Button{

        id:btnConnectSer4
        anchors.left: btnConnectSer5.right
        anchors.leftMargin: 10
        anchors.top: btnConnectSer5.top
        text:"getserverlist"
        onClicked: {

            //var data={ "username":"admin","oldpassword":"admin","newpassword":"newpassword"};

            mqtttest.publishMsg("getserverlist",null);
        }
    }

    MqttTest{

        id:mqtttest

    }
}
