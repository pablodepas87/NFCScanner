import QtQuick 2.0

Rectangle {
    id:tagconnectivity
    width: parent.width * 0.95
    height: parent.height * 0.06
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: parent.top
    anchors.topMargin: parent.height * 0.02
    radius: 2
    border.color: "white"
    border.width: 2

    states: [
        State {
            when : !NFCManager.targetConnected
            PropertyChanges {
                target: tagconnectivity
                color: "#EE204D"
            }
            PropertyChanges {
                target: txtTagConnectivity
                text:"Tag not connected"
            }
        },
        State{
            when : NFCManager.targetConnected
            PropertyChanges {
                target: tagconnectivity
                color: "#90ee90"
            }
            PropertyChanges {
                target: txtTagConnectivity
                text:"Tag connected"
            }
        }
    ]

    Text {
        id: txtTagConnectivity
        anchors.fill: parent
        fontSizeMode: Text.Fit
        minimumPixelSize: 15
        font.pixelSize: 20
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.capitalization: Font.AllUppercase
    }
}
