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

    Connections {
        id: connectionsSender

        function onBytesWritten() {
            textAreaLogs.text += Qt.formatDateTime(
                        new Date(),
                        "hh:mm:ss:zzz [dd.MM.yy]") + ": message was send\n"
        }

        function onReadySend() {
            textAreaLogs.text += Qt.formatDateTime(
                        new Date(),
                        "hh:mm:ss:zzz [dd.MM.yy]") + ": message ready to send\n"
        }

        function onDisconnected() {
            textAreaLogs.text += Qt.formatDateTime(
                        new Date(),
                        "hh:mm:ss:zzz [dd.MM.yy]") + ": Sender socket disconnect\n"
        }

        function onConnected() {
            textAreaLogs.text += Qt.formatDateTime(
                        new Date(),
                        "hh:mm:ss:zzz [dd.MM.yy]") + ": Sender socket connect\n"
        }

        function onStateChanged(state) {
            var stateName
            switch (state) {
            case 0:
                stateName = "Unconnected State"
                break
            case 1:
                stateName = "HostLookup State"
                break
            case 2:
                stateName = "Connecting State"
                break
            case 3:
                stateName = "Connected State"
                break
            case 4:
                stateName = "Bound State"
                break
            case 6:
                stateName = "Closing State"
                break
            case 5:
                stateName = "Listening State"
                break
            default:
                stateName = "Unknown State"
                break
            }
            textAreaLogs.text += Qt.formatDateTime(new Date(),
                                                   "hh:mm:ss:zzz [dd.MM.yy]")
                    + ": Sender socket state was changed on: " + stateName + "\n"
        }
        target: sender
    }

    Connections {
        id: connectionsReceiver

        function onReadyRead() {
            textAreaLogs.text += Qt.formatDateTime(
                        new Date(),
                        "hh:mm:ss:zzz [dd.MM.yy]") + ": message ready to read\n"
        }

        function onMessageWasRead() {
            textAreaLogs.text += Qt.formatDateTime(
                        new Date(),
                        "hh:mm:ss:zzz [dd.MM.yy]") + ": message was read\n"
        }

        function onDisconnected() {
            textAreaLogs.text += Qt.formatDateTime(
                        new Date(),
                        "hh:mm:ss:zzz [dd.MM.yy]") + ": Receiver socket disconnect\n"
        }

        function onConnected() {
            textAreaLogs.text += Qt.formatDateTime(
                        new Date(),
                        "hh:mm:ss:zzz [dd.MM.yy]") + ": Receiver socket connect\n"
        }

        function onStateChanged(state) {
            var stateName
            switch (state) {
            case 0:
                stateName = "Unconnected State"
                break
            case 1:
                stateName = "HostLookup State"
                break
            case 2:
                stateName = "Connecting State"
                break
            case 3:
                stateName = "Connected State"
                break
            case 4:
                stateName = "Bound State"
                break
            case 6:
                stateName = "Closing State"
                break
            case 5:
                stateName = "Listening State"
                break
            default:
                stateName = "Unknown State"
                break
            }
            textAreaLogs.text += Qt.formatDateTime(new Date(),
                                                   "hh:mm:ss:zzz [dd.MM.yy]")
                    + ": Receiver socket state was changed on: " + stateName + "\n"
        }

        target: receiver
    }
}
