import QtQuick
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

import "../Objects"
import ConstData 1.0

//-----------------------------------------------------------------//
//                           Класс еды                             //
//-----------------------------------------------------------------//

Rectangle {
    
    id: food

    property int identifier : -1
    //property variant animRotation: animRotation
    property variant animOpacity: animOpacity
    property int type: EnObjType.EnFood

    // Сигнал создания нового объекта
    signal sigCreateNewFood();

    // Старт моделирования объекта
    function start() {
        GameProcess.vCreateObject(type, identifier, x, y, width, height, 0, 0);
    }
    
    width: 100
    height: width
    radius: height / 3
    opacity: 0

    color: "transparent"

    // Изображение еды
    Image {

        id: imgFood

        smooth: true
        visible: false

        source: "../Images/food.svg"
        sourceSize.width: parent.width
        sourceSize.height: parent.height
    }

    // Тень
    DropShadow {
        anchors.fill: imgFood
        radius: 5
        color: "gray"
        horizontalOffset: 2
        verticalOffset: 1
        source: imgFood
        smooth: true
        transparentBorder: true
    }

    // Анимация появления
    NumberAnimation on opacity {

        id: animOpacity

        to: 1
        duration: 1000
    }
}
