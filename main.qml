import QtQuick
import QtQuick.Window
import QtQuick.Controls
import Qt5Compat.GraphicalEffects

import "Scenes"
import "Objects"
import "Widgets"

ApplicationWindow {

    id: app

    visible: true
    visibility: "FullScreen"

    title: qsTr("BrandNewApp")

    // Главная страница
    Page {
        id: mainPage
        anchors.fill: parent

        // Игровая сцена
        GameScene {
            id: rectMainWindow
            anchors.fill: parent
        }

        // Кнопка выхода
        Button {
            id: buttonExit
            text: qsTr("X");

            height: rectMainWindow.height / 25
            width: height
            radius: height

            anchors.right: parent.right
            anchors.top: parent.top
            anchors.rightMargin: height
            anchors.topMargin: height

            onClicked: {
                app.close();
            }
        }
    }

}
