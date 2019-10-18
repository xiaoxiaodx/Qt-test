import QtQuick 2.0

Rectangle {

    id:root

    property int mulitiScreen: 2

    property alias myModel: myModel

    ListModel {
        id:myModel



        ListElement {
                  name: "Apple"
                  cost: 2.45
              }
              ListElement {
                  name: "Orange"
                  cost: 3.25
              }
              ListElement {
                  name: "Banana"
                  cost: 1.95
              }
    }

    Repeater{

        model: myModel

        Component.onCompleted: {

            console.debug("11********"+mulitiScreen +"  "+root.width )
        }


        Rectangle{


            width: parent.width/mulitiScreen
            height:  parent.height/mulitiScreen
            x:Math.floor(model.index/mulitiScreen * width)
            y:model.index%mulitiScreen * height

            border.width: 5
            border.color: "red"



            color: "black"
        }



    }

}
