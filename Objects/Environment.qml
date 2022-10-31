import QtQuick
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

//-----------------------------------------------------------------//
//                              Холмы                              //
//-----------------------------------------------------------------//

Row {
    
    id: hills
    
    property variant platform

    // Солнце
    Rectangle {

        id: sun

        height: rectMainWindow.height / 8
        width: height
        radius: height

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: height * 1.5
        anchors.topMargin: height

        color: "lightyellow"

        // Эффект свечения
        layer.enabled: true
        layer.effect: Glow {
            radius: sun.radius / 0.5
            spread: 0.3
            //samples: radius * 1.5
            color: "lightyellow"
            transparentBorder: true
        }
    }

    Rectangle {
        
        id: firstHill
        
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -height / 7.5
        anchors.horizontalCenter: parent.horizontalCenter
        
        height: parent.width / 1.7
        width: height
        radius: height
        color: "transparent"

        // Изображение холма
        Image {

            id: imgFirstHill

            smooth: true

            source: "../Images/hill.svg"
            sourceSize.width: parent.width
            sourceSize.height: parent.height

        }
        
        layer.enabled: true
        layer.effect: DropShadow {
            radius: 10
            color: "gray"
            horizontalOffset: 7
            verticalOffset: -5
            transparentBorder: true
        }
    }
    
    Rectangle {
        
        id: secondHill
        
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -height / 4.5
        anchors.right: parent.right
        
        height: parent.width / 3
        width: height
        radius: height
        color: "transparent"

        // Изображение холма
        Image {

            id: imgSecondHill

            smooth: true
            mirror: true

            source: "../Images/hill.svg"
            sourceSize.width: parent.width
            sourceSize.height: parent.height
        }
        
        layer.enabled: true
        layer.effect: DropShadow {
            radius: 10
            //samples: radius * 1.5
            color: "gray"
            horizontalOffset: 7
            verticalOffset: -3
            transparentBorder: true
        }
    }
    
    Rectangle {
        
        id: thirdHill
        
        y: parent.height - height / 10
        
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -height / 6
        anchors.left: parent.left
        anchors.leftMargin: -height / 13

        height: parent.width / 3
        width: height
        radius: height
        color: "transparent"

        // Изображение холма
        Image {

            id: imgThirdHill

            smooth: true

            source: "../Images/hill.svg"
            sourceSize.width: parent.width
            sourceSize.height: parent.height
        }
        
        layer.enabled: true
        layer.effect: DropShadow {
            radius: 10
            //samples: radius * 1.5
            color: "gray"
            horizontalOffset: 2
            verticalOffset: -2
            transparentBorder: true
        }
    }
    
}
