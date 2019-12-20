import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import SceneGraphRendering 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Renderer{
        anchors.fill: parent
        videoSource: "F:/迅雷下载/智慧园区管理平台演示视频.wmv"
        Text {
            id: name
            anchors.centerIn: parent
            color: "red"
            font.pixelSize: 18
            text: qsTr("text")
        }
    }
}
