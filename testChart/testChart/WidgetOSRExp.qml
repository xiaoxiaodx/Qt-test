import QtQuick 2.3
import QtQuick.Window 2.2

import Diy.WidgetOSRItem 1.0

Rectangle
{
    id: osrRoot
    property alias osrItem_OSRWidget : osrItem.osrWidget

    x:100
    y:100
    width: 800
    height: 600

    WidgetOSRItem //OSR ITEM
    {
        id: osrItem
        anchors.fill:parent

        MouseArea//控制osrItem的焦点
        {
            anchors.fill: parent;
            propagateComposedEvents: true

            onPressed:
            {
                mouse.accepted = false
                parent.focus = true
            }
            onReleased: mouse.accepted = false
            onMouseXChanged: mouse.accepted = false
            onMouseYChanged: mouse.accepted = false
        }
    }
}
