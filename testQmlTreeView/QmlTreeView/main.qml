import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 1.4
import MyTreeModel 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MyTreeModel {
        id: theModel
    }

    Component {
        id: sectionHeading
        Rectangle {
            width: container.width
            height: childrenRect.height
            color: "black"

            Text {
                text: section
                font.bold: true
                font.pixelSize: 20
            }
        }
    }
    TreeView {
        anchors.fill: parent
        model: theModel
        itemDelegate: Rectangle {
            //color: ( styleData.row % 2 == 0 ) ? "white" : "lightblue"

            height: 20

            Text {
                anchors.verticalCenter: parent.verticalCenter
                //color:  styleData.textColor
                text: styleData.value === undefined ? "" : styleData.value // The branches don't have a description_role so styleData.value will be undefined
            }
        }




        section.property: "size"
        section.criteria: ViewSection.FullString
        section.delegate: sectionHeading
        TableViewColumn {
            role: "name_role"
            title: "Name"
        }
        TableViewColumn {
            role: "description_role"
            title: "Description"
        }

        TableViewColumn {
            role: "hello"
            title: "HELLO"
        }
    }
}
