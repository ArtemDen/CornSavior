import QtQuick
import Qt5Compat.GraphicalEffects

//-----------------------------------------------------------------//
//                     Класс прозрачной кнопки                     //
//-----------------------------------------------------------------//

Rectangle {

    id: button

    property alias text: textButton.text
    property alias fontSize: textButton.font.pointSize

    width: 300
    height: 50
    radius: 50
    color: "transparent"

    // Сигнал нажатия
    signal clicked()

    // Текст кнопки
    Text {

        id: textButton

        anchors.centerIn: parent
        font.family: "Comic Sans MS"
        font.pointSize: parent.width / 1.5
        font.bold: true
        text: qsTr("text")
        color: "lightyellow"
        opacity: 0.9
    }

    // Эффект тени
    layer.enabled: true
    layer.effect: DropShadow {
        anchors.fill: button
        horizontalOffset: mouse.containsPress ? button.height / 40.0 : button.height / 28.0
        verticalOffset: mouse.containsPress ? button.height / 38.0 : button.height / 26.0
        radius: 8
        //samples: 17
        color: "gray"
        source: button
        transparentBorder: true
    }
    
    // Реакция на нажатие
    MouseArea {

        id: mouse

        anchors.fill: parent
        onClicked: {
            button.clicked();
        }
    }
}
