import QtQuick 2.12
import Qt5Compat.GraphicalEffects

import "../Objects"
import ConstData 1.0

//-----------------------------------------------------------------//
//                          Класс орудия                           //
//-----------------------------------------------------------------//

Rectangle {

    id: weapon
    
    property int identifier : -1
    property int type: EnObjType.EnWeapon
    property alias mouse: mouseWeapon

    // Ссылки на объект платформы и пунктирной линии
    property var platform
    property var line

    // Сигнал создания нового объекта
    signal sigCreateNewWeapon();

    // Сигнал об уничтожении орудия
    signal sigToDestroy(var identifier);

    // Старт моделирования объекта
    function start() {

        var diffX = platform.x + platform.width / 2 - x - width / 2;
        var diffY = y + height / 2 - platform.y + 1;
        var distance = Math.sqrt(Math.pow(diffX, 2) + Math.pow(diffY, 2));
        var angle = 0;

        if (diffX >= 0) {
            angle = Math.atan(diffY / diffX);
        }
        else {
            angle = Math.atan(diffY / diffX) + Math.PI;
        }

        GameProcess.vCreateObject(type, identifier, x, y, width, height, distance * 10, angle);
        timerNewWeapon.start();
    }
    
    width: 100
    height: width
    radius: width
    opacity: 0
    
    gradient: "AboveTheSky"
    
    layer.enabled: true
    layer.effect: DropShadow {
        radius: 5
        color: "gray"
        horizontalOffset: 1
        verticalOffset: 2
        transparentBorder: true
    }

    // Анимация появления
    NumberAnimation on opacity {
        to: 1
        duration: 500
    }

    // Таймер создания нового объекта
    Timer {
        id: timerNewWeapon

        interval: 1000
        repeat: false

        onTriggered: {
            sigCreateNewWeapon();
        }
    }
    
    MouseArea {
        id: mouseWeapon
        anchors.fill: parent
        
        // "Оттягивание" объекта для задания начальной скорости
        drag {
            target: weapon
            
            maximumY: weapon.parent.height - parent.height
            minimumY: weapon.parent.height - 2 * platform.height
            
            maximumX: platform.x * 2
            minimumX: 0

            onActiveChanged: {
                if(!drag.active) {
                    start();
                }
                else {
                    line.opacity = 1;
                }
            }
        }

        onReleased: {
            if (line.opacity) {
                line.opacity = 0;
                mouseWeapon.enabled = false;
            }
        }
        
        onPositionChanged: {
            if (drag.active) {
                line.requestPaint();
            }
        }
    }

    onXChanged: {
        if (x < -width || x > parent.width) {
            sigToDestroy(identifier);
            if (timerNewWeapon.running) {
                timerNewWeapon.stop();
                sigCreateNewWeapon();
            }
        }
    }

    onYChanged:  {
        if (y > parent.height) {
            sigToDestroy(identifier);
            if (timerNewWeapon.running) {
                timerNewWeapon.stop();
                sigCreateNewWeapon();
            }
        }
    }
}
