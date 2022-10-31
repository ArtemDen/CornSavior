import QtQuick
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

import "../Objects"

//-----------------------------------------------------------------//
//                           Сцена игры                            //
//-----------------------------------------------------------------//

Column {
    
    id: infoWidget
    
    property variant windowSize: 0
    property alias model: repeater.model
    property alias aimCount: rowAimCount.aimCount
    property alias cornCounter: repeater
    
    spacing: 10
    
    // Счетчик еды
    Rectangle {
        
        id: rectFoodCount
        
        property int foodCount : 10
        
        color: "lightgray"
        
        width: windowSize.width / 5
        height: windowSize.height / 17
        radius: 15
        
        border.width: 1
        border.color: "gray"
        
        anchors.horizontalCenter: rowAimCount.horizontalCenter

        LinearGradient {

            anchors.fill: parent
            source: parent
            opacity: 0.1

            GradientStop {
                position: 0.5
                color: "white"
            }
            GradientStop {
                position: 1.0
                color: "black"
            }
        }
        
        Row {
            
            anchors.centerIn: parent
            spacing: windowSize.width / 385
            
            Repeater {
                
                id: repeater
                
                anchors.fill: parent
                model: 10
                
                delegate: Food {
                    x: 0
                    y: 0
                    width: rectFoodCount.width / 13
                    opacity: 1
                    Component.onCompleted: {
                        //animRotation.stop();
                        animOpacity.stop();
                    }
                }
            }
        }
    }
    
    // Счетчик сбитых целей
    Row {
        
        id: rowAimCount
        
        property int aimCount : 0
        anchors.horizontalCenter: parent.horizontalCenter

        Aim {
            
            id: imageAim
            
            x: 0
            y: 0
            width : windowSize.width / 25
            height : width
        }

        // Шрифт
        FontLoader {
            id: fontCustom
            source: "../fonts/comic.ttf"
        }
        
        Text {
            anchors.verticalCenter: imageAim.verticalCenter
            font.family: fontCustom.name
            font.pointSize: imageAim.width / 2.5
            font.bold: true
            color: "black"
            opacity: 0.5
            text: " x " + parent.aimCount
        }
    }
}
