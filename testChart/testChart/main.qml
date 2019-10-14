import QtQuick 2.12
import QtQuick.Window 2.12

import BarChart 1.0


Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")


    BarChart{
        id:barchart
        anchors.fill: parent

        onWidthChanged: {
            console.debug("onWidthChanged")

            setCoordinateOriginX(50)
        }
        onHeightChanged: {
            setCoordinateOriginY(height-50)
            console.debug("onHeightChanged")
        }

        Component.onCompleted: {

             console.debug("onCompleted")
            setUnitScale(5,5)

        }

    }
}
