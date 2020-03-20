import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")



    ListModel{
        id:listDeviceDataModel
        ListElement { ip: "218.76.52.29";port: "555"}
        ListElement { ip: "218.76.52.29";port: "555"}
        ListElement { ip: "218.76.52.29";port: "555"}
        ListElement { ip: "218.76.52.29";port: "555"}

        ListElement { ip: "218.76.52.29";port: "555"}
        ListElement { ip: "218.76.52.29";port: "555"}
        ListElement { ip: "218.76.52.29";port: "555"}
        ListElement { ip: "218.76.52.29";port: "555"}

        ListElement { ip: "218.76.52.29";port: "555"}
        ListElement { ip: "218.76.52.29";port: "555"}
        ListElement { ip: "218.76.52.29";port: "555"}
        ListElement { ip: "218.76.52.29";port: "555"}

        ListElement { ip: "218.76.52.29";port: "555"}
        ListElement { ip: "218.76.52.29";port: "555"}
        ListElement { ip: "218.76.52.29";port: "555"}
        ListElement { ip: "218.76.52.29";port: "555"}
    }
    VedioLayout{
        id: vedioLayout

        anchors.fill: parent

        myLayoutSquare:4

        myModel: listDeviceDataModel

    }
}
