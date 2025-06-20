import QtQuick 6.5
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls 6.5

Window {
    id: winApp

    width: 640
    height: 480
    minimumWidth: 400
    minimumHeight: 350
    visible: true
    title: qsTr("udp logger")
    color: "#1c1c1c"

    ColumnLayout {
        id: columnLayoutMain

        anchors.fill: parent
        anchors.margins: 5
        spacing: 10

        RowLayout {
            id: rowLayoutMain

            Layout.alignment: Qt.AlignHCenter
            spacing: 16

            Rectangle {
                id: rectTransmitterModule

                Layout.preferredHeight: 175
                Layout.minimumWidth: 175
                Layout.fillWidth: true
                Layout.leftMargin: 5
                color: "#707070"
                radius: 10

                ColumnLayout {
                    id: columnLayoutInput

                    anchors.fill: parent
                    anchors.margins: 5

                    ScrollView {
                        id: scrollViewInput

                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        TextArea {
                            id: textAreaInput

                            placeholderText: "put your message"
                            wrapMode: Text.Wrap
                            font.pointSize: 12
                            selectionColor: "darkred"
                            Universal.accent: "darkred"
                        }
                    }

                    Button {
                        id: btnSend

                        text: "SEND"
                        icon.source: "images/send.svg"
                        Layout.preferredWidth: 100

                        onClicked: {
                            sender.readySend(textAreaInput.text)
                        }
                    }
                }
            }

            Rectangle {
                id: rectReceiverModule

                Layout.preferredHeight: 175
                Layout.minimumWidth: 175
                Layout.fillWidth: true
                Layout.rightMargin: 5
                color: "#707070"
                radius: 10

                Rectangle {
                    id: rectOutputTextBackground

                    color: "transparent"
                    anchors.fill: parent
                    anchors.margins: 5
                    border.color: "#1c1c1c"
                    border.width: 1

                    ScrollView {
                        id: scrollViewOutput

                        anchors.fill: parent
                        anchors.margins: 4
                        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                        ScrollBar.vertical.policy: ScrollBar.AsNeeded

                        TextArea {
                            id: textAreaOutput

                            text: ""
                            color: "black"
                            font.family: "Times New Roman"
                            font.pointSize: 14
                            font.italic: true
                            readOnly: true
                            wrapMode: Text.Wrap
                            selectionColor: "darkgreen"
                            Universal.accent: "darkgreen"
                        }
                    }
                }
            }
        }

        Rectangle {
            id: rectLine

            Layout.preferredHeight: 3
            Layout.preferredWidth: winApp.width - 20
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
            color: "darkgreen"
        }

        Logger {
            id: loggerLogger

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
        }

        Connections {
            id: connectionsMain

            function onMessageWasRead(message) {
                textAreaOutput.text = message
            }

            target: receiver
        }
    }
}
