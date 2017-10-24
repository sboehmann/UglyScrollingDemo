import QtQuick 2.9
import Demo 1.0

Rectangle {
    id: root

    property int screen: 0
    property alias first: vp.first
    property alias last: vp.last
    property alias position: vp.position

    color: screen % 2 == 0 ? "lightgrey" : "grey"

    Text {
        id: title
        text: "Window " + screen
        font.bold: true
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 18
    }

    View {
        id: vp
        anchors.top: title.bottom
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
    }
}
