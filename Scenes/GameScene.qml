import QtQuick
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects

import "../Objects"
import "../Widgets"
import ConstData 1.0

//-----------------------------------------------------------------//
//                           Сцена игры                            //
//-----------------------------------------------------------------//

Rectangle {

    id: rectMainWindow

    // Массив орудий
    property variant arrObjects: []
    property int globalCounter: 0

    // Создание нового объекта орудия
    function createWeapon() {
        var componentWeapon = Qt.createComponent("../Objects/Weapon.qml");
        if (componentWeapon.status === Component.Ready) {
            var objWeapon = componentWeapon.createObject(rectMainWindow);
            objWeapon.platform = platform;
            objWeapon.line = line
            objWeapon.identifier = globalCounter
            objWeapon.width = platform.width * 2.;
            objWeapon.x = platform.x + platform.width / 2 - objWeapon.width / 2
            objWeapon.y = platform.y - objWeapon.height / 2
            objWeapon.sigCreateNewWeapon.connect(createWeapon);
            objWeapon.sigToDestroy.connect(deleteObj);
            arrObjects.push(objWeapon);
            line.weapon = objWeapon;
            globalCounter++;
        }
    }

    // Создание нового объекта цели
    function createAim() {
        var componentAim = Qt.createComponent("../Objects/Aim.qml");
        if (componentAim.status === Component.Ready) {
            var objAim = componentAim.createObject(rectMainWindow);
            objAim.identifier = globalCounter;
            objAim.width = parent.width / 20;
            objAim.x = parent.width;
            objAim.y = Math.random() * (parent.height - 2.5 * objAim.amplitude) + objAim.amplitude;
            objAim.start();
            objAim.sigCreateNewAim.connect(createAim);
            objAim.sigIsHit.connect(countHitAim);
            objAim.sigToDestroy.connect(deleteObj);
            arrObjects.push(objAim);
            globalCounter++;
        }
    }

    // Создание нового объекта еды
    function createFood() {
        var componentFood = Qt.createComponent("../Objects/Food.qml");
        if (componentFood.status === Component.Ready) {
            var objFood = componentFood.createObject(rectMainWindow);
            objFood.identifier = globalCounter;
            objFood.width = parent.width / 30
            objFood.x = Math.random() * parent.width / 2 + parent.width / 3
            objFood.y = Math.random() * parent.height / 1.5 + 2 * objFood.height
            objFood.start();
            objFood.sigCreateNewFood.connect(createFood);
            arrObjects.push(objFood);
            globalCounter++;
        }
    }

    // Уничтожение объекта
    function deleteObj(identifier) {
        GameProcess.sigDeleteObject(identifier);
        arrObjects[identifier].destroy();
        arrObjects[identifier] = 0;
    }

    // Счетчик
    function countHitAim() {
        infoWidget.aimCount++
    }

    // Начальная инициализация
    function init() {
        createFood();
        createFood();
        createWeapon();
        createAim();
    }

    // Конец игры
    function gameover() {
        gameoverWidget.open();
        infoWidget.z = 1;
        for (let i = 0; i <= arrObjects.length; i++) {
            if (arrObjects[i]) {
                GameProcess.sigDeleteObject(i);
                //arrObjects[i].destroy();

                switch(arrObjects[i].type) {
                case EnObjType.EnWeapon:
                    arrObjects[i].sigCreateNewWeapon.disconnect(createWeapon);
                    arrObjects[i].sigToDestroy.disconnect(deleteObj);
                    arrObjects[i].mouse.enabled = false;
                    break;
                case EnObjType.EnAim:
                    arrObjects[i].sigCreateNewAim.disconnect(createAim);
                    arrObjects[i].sigIsHit.disconnect(countHitAim);
                    arrObjects[i].sigToDestroy.disconnect(deleteObj);
                    break;
                case EnObjType.EnObject:
                    arrObjects[i].sigCreateNewFood.disconnect(createFood);
                    break;
                }
            }
        }
    }

    gradient: "NewYork"

    // Платформа орудия
    Rectangle {

        id: platform

        width: parent.width / 47.5
        height: parent.height / 4
        radius: width

        gradient: "JuicyPeach"

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0.25 * height
        anchors.left: parent.left
        anchors.leftMargin: width * 6

        layer.enabled: true
        layer.effect: DropShadow {
            radius: 5
            spread: 0.0
            //samples: radius * 1.5
            color: "gray"
            horizontalOffset: 1
            verticalOffset: 1
            transparentBorder: true
        }
    }

    // Холмы
    Environment {

        id: hills

        height: parent.height
        width: parent.width
        opacity: 0.9

        platform: platform
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
    }

    // Пунктирная линия траектории орудия
    Canvas {

        id: line

        anchors.fill: parent

        property var weapon

        renderStrategy: Canvas.Threaded

        onPaint: {
            //var ctx = getContext("2d");
            //ctx.reset();
            //ctx.strokeStyle = "lightgray";
            ////ctx.setLineDash([3, 3]);
            //ctx.beginPath();
            //ctx.moveTo(weapon.x + weapon.width / 2, weapon.y + weapon.height / 2);
            //ctx.lineTo(platform.x + platform.width / 2, platform.y - 1);
            //ctx.stroke();
        }
    }

    // Отображение информации
    InfoWidget {

        id: infoWidget

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: parent.height / 15

        windowSize: rectMainWindow
    }

    // Виджет окончания игры
    GameOverWidget {

        id: gameoverWidget

        x: 0
        y: parent.height
    }

    Component.onCompleted: {
        init();
    }

    Connections {
        target: GameProcess
        function onSigSendCoordToQML(ID, X, Y) {
            arrObjects[ID].x = X;
            arrObjects[ID].y = Y;
        }
        function onSigFoodIsEaten(ID) {
            deleteObj(ID);
            createFood();
            for (var i = infoWidget.cornCounter.count - 1; i >= 0; i--) {
                if (infoWidget.cornCounter.itemAt(i).opacity === 1) {
                    infoWidget.cornCounter.itemAt(i).opacity = 0.25;
                    //infoWidget.model = arrFood;
                    if (i === 0) {
                       gameover();
                    }
                    break;
                }
            }
        }
    }

    Connections {
        target: gameoverWidget
        function onSigRestart() {

            for (var i = 0; i <= arrObjects.length; i++) {
                if (arrObjects[i]) {
                    arrObjects[i].destroy();
                }
            }
            arrObjects = [];

            for (var j = infoWidget.cornCounter.count - 1; j >= 0; j--) {
                infoWidget.cornCounter.itemAt(j).opacity = 1;
            }

            globalCounter = 0;

            infoWidget.aimCount = 0;
            init();
        }
    }
}
