import QtQuick 2.0
import Mediabase 1.0
import QtQuick.Controls 1.4
Rectangle {

    signal doubleClick(bool isFullScreen);
    signal click();
    signal s_showToastMsg(string str)
    signal s_deleteObject()

    property string mip: ""
    property string mport: ""
    property string mID: ""
    property string mAcc: ""
    property string mPwd: ""
    property bool mIsCreateConenect: false
    property bool mIsPlayAudio: false
    property bool mIsSelected: false
    property bool mIsRecordVedio: false


    property alias logId: video.logIdentity

    property string shotScrennFilePath: ""
    property string recordingFilePath: ""

    border.color: mIsSelected?"red":"white"
    border.width: 2

    onMIsCreateConenectChanged: {
        console.debug("onMXVideoIsCreateTcpConnectChanged   "+ mIsCreateConenect)
        if(mIsCreateConenect){
            video.sendAuthentication(mID,mAcc,mPwd);
            video.connectServer(mip,mport)
        }else{
            video.disConnectServer();
        }
    }

    onMIsPlayAudioChanged: video.funPlayAudio(mIsPlayAudio)

    onShotScrennFilePathChanged: video.funSetShotScrennFilePath(shotScrennFilePath);

    onRecordingFilePathChanged: video.funSetRecordingFilePath(recordingFilePath)

    Mediabase{
        id:video



        anchors.fill: parent
        anchors.margins: 2

        property  bool voiceSwitch: false
        property bool mXVideoPlayAudio: mIsPlayAudio
        property bool mXVideoRecordVedio: mIsRecordVedio
        property bool mXVideoIsCreateTcpConnect: mIsCreateConenect

        onSignal_loginStatus: s_showToastMsg(msg);


        Component.onCompleted: {




            video.connectServer(mip,mport);

        }
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            propagateComposedEvents:true

            onClicked: click();

            onDoubleClicked:doubleClick(true);
        }

        Image {
            id: img_delete
            x:parent.x + parent.width - img_delete.width

            source: "qrc:/images/img_delete.png"

            MouseArea{
                anchors.fill: parent
                enabled: true

                onClicked: {
                    s_deleteObject();
                }

                onDoubleClicked: {
                    //console.debug("1000")
                }

            }
        }



        Rectangle{
            id:btnFunction
            anchors.bottom: parent.bottom
            height: 30
            width: parent.width

            color: "#33000000"


            Row{

                height: parent.height

                Button{
                    id:authuor
                    text: "发送鉴权"
                    anchors.verticalCenter: parent.verticalCenter

                    onClicked: {
                        video.sendAuthentication("INEW-003831-KYGRD","admin","admin");
                       // video.sendAuthentication("INEW-003882-RHHFR","admin","admin");

                    }
                }

                Button{
                    id:switchVoice
                    text: "声音开关"
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {

                        video.funPlayAudio(true)

                    }
                }

                Button{
                    id:record
                    text: "录像"
                    anchors.verticalCenter: parent.verticalCenter
                }

                Button{
                    id:shotScreen
                    text: "截图"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }


        }


    }
}



