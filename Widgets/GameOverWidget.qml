import QtQuick
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

import "../Objects"
import "../Widgets"

//-----------------------------------------------------------------//
//                    Виджет окончания игры                        //
//-----------------------------------------------------------------//

Rectangle {

    // Открыть виджет
    function open() {
        animUp.start();
        z = 1;
    }
    
    id: gameOverWidget
    
    width: parent.width
    height: parent.height
    
    color: "transparent"

    // Сигнал перезапуска игры
    signal sigRestart();
    
    Rectangle {
        anchors.fill: parent
        color: "lightgray"
        opacity: 0.65
    }

    // Шрифт
    FontLoader {
        id: fontCustom
        source: "../fonts/comic.ttf"
    }
    
    StyleText {

        id: gameoverText

        anchors.centerIn: parent
        textString: qsTr("GAME OVER")
        fontName: fontCustom.name
        fontSize: parent.height / 6
    }

    NumberAnimation on y {
        id: animUp
        to: 0
        duration: 1000
        running: false
    }

    NumberAnimation on y {
        id: animDown
        to: height
        duration: 1000
        running: false
    }

    Button {

        id: buttonRestart

        text: qsTr("Restart");

        height: parent.height / 10
        width: parent.width / 5
        radius: height
        fontSize: width / 5

        anchors.horizontalCenter: gameoverText.horizontalCenter
        anchors.top: gameoverText.bottom
        anchors.topMargin: 50

        onClicked: {
            sigRestart();
            animDown.start();
        }
    }
}
