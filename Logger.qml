import QtQuick 6.5
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls 6.5

Rectangle {
    id: rectRoot

    color: "#707070"

    ColumnLayout {
        id: columnLayoutMain

        anchors.fill: parent
        anchors.margins: 5

        Text {
            id: textTitle

            font.pointSize: 10
            color: "black"
            text: qsTr(" logger")
        }

        ScrollView {
            id: scrollViewLogs

            Layout.fillWidth: true
            Layout.fillHeight: true
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn
            clip: true

            TextArea {
                id: textAreaLogs

                font.pointSize: 12
                color: "black"
                text: qsTr("START LOGGING:")
                readOnly: true
                wrapMode: Text.Wrap
                textFormat: TextEdit.RichText
                background: Rectangle {
                    color: "transparent"
                    border.color: "black"
                    border.width: 1
                }
            }
        }
    }

    Item {
        id: itemSocketsColors

        property var colors: ["darkgreen", "darkorange", "darkviolet", "darkblue"]
        property var sockets: []
    }

    Connections {
        id: connectionsLog

        function onEventDetected(id, description) {
            if (itemSocketsColors.sockets.indexOf(id) === -1) {
                itemSocketsColors.sockets.push(id)
            }
            var currentColor = itemSocketsColors.colors[itemSocketsColors.sockets.indexOf(
                                                            id) % 4]
            textAreaLogs.text += Qt.formatDateTime(
                        new Date(),
                        "hh:mm:ss:zzz [dd.MM.yy]") + ": <font color="
                    + currentColor + ">-" + id + "-</font> " + description + "\n"
        }

        target: logger
    }
}
