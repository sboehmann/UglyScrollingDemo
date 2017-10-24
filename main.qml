import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Demo 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Scrolling PoC")

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0

            ViewerWindow {
                id: vp1
                screen: 1
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            ViewerWindow {
                id: vp2
                screen: 2
                first: vp1.last
                position: vp1.position - vp1.width
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            ViewerWindow {
                id: vp3
                screen: 3
                first: vp2.last
                position: vp2.position - vp2.width
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }

        ScrollBar {
            Layout.fillWidth: true
            Layout.preferredHeight: 25
            orientation: Qt.Horizontal
            policy: ScrollBar.AlwaysOn
            position: 0
            onPositionChanged: vp1.position = position * root.width
            size: 0.025
        }
    }
}
