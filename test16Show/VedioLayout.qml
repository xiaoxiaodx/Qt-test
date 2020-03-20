import QtQuick 2.0

Rectangle {

    id:root

    property int myLayoutSquare: 2  //几乘几的显示
    property alias myModel: repeater.model
    property int currentIndex: -1
    property string shotScreenFilePath1: ""
    property string recordingFilePath1: ""

    Repeater{
        id:repeater

        VideoLivePlay{
            id:video
            width: root.width/myLayoutSquare
            height:  root.height/myLayoutSquare

            x:(index%myLayoutSquare) * width
            y:Math.floor(index/myLayoutSquare) * height

            mip:ip
            mport: port
            logId:index
            onS_deleteObject: {
                listDeviceDataModel.remove(index)
            }

        }
    }

}
