import QtQuick
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

import "../Objects"
import ConstData 1.0

//-----------------------------------------------------------------//
//                           Класс цели                            //
//-----------------------------------------------------------------//

Rectangle {

    id: aim

    property int identifier : -1
    property int amplitude: 2 * height
    property int type: EnObjType.EnAim

    // Сигнал создания новой цели
    signal sigCreateNewAim();

    // Сигнал о сбитии цели
    signal sigIsHit()

    // Сигнал об уничтожении цели
    signal sigToDestroy(var identifier);

    // Старт моделирования объекта
    function start() {
        var speed = width * 2 + identifier;
        GameProcess.vCreateObject(type, identifier, x, y, width, height, speed, amplitude);
        timerNewAim.start();
    }

    width: 100
    height: width

    color: "transparent"
    visible: true
    opacity: 0.7

    // Изображение цели
    Image {

        id: imgAim

        smooth: false
        visible: false
        asynchronous: true

        source: "../Images/aim.svg"
        sourceSize.width: parent.width
        sourceSize.height: parent.height
    }

    // Тень
    DropShadow {
        anchors.fill: imgAim
        radius: 8
        color: "gray"
        horizontalOffset: 3
        verticalOffset: 2
        source: imgAim
        smooth: true
        transparentBorder: true
    }

    // Таймер создания нового объекта
    Timer {

        id: timerNewAim

        interval: Math.random() * 2000 + 5000
        repeat: false

        onTriggered: {
            sigCreateNewAim();
        }
    }

    onXChanged: {
        if (x < -width) {
            sigToDestroy(identifier);
            if (timerNewAim.running) {
                timerNewAim.stop();
                sigCreateNewAim();
            }
        }
    }

    onYChanged:  {
        if (y > parent.height) {
            sigIsHit();
            sigToDestroy(identifier);
            if (timerNewAim.running) {
                timerNewAim.stop();
                sigCreateNewAim();
            }
        }
    }
}
