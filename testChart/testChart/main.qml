import QtQuick 2.12
import QtQuick.Window 2.12
import BarChart 1.0
import ChartPolyLine 1.0
import QtQuick.Controls 1.4
import ChartPie 1.0
import ChartBar 1.0


Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")



    Button{

        id:btn_axisAnimation

        z:1
        text: "轴动画"


        onClicked: {

            barchart.startAxisAnimation(800);
        }
    }

    Button{

        id:btn_chartAnimation
        z:1
        text: "图形动画"
        anchors.left: btn_axisAnimation.right
        onClicked: {
            barchart.startChartAnimation(600);
        }

    }

    ChartBar{
        id:barchart
        anchors.fill: parent

        z:0
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
