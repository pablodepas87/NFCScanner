import QtQuick 2.14
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 800
    height: 480
    title: qsTr("Hello World")
    background: Rectangle{
          color: "#166ab3"
    }

    Item{
        id: preTargetFoundItem
        visible: !NFCManager.targetConnected
        anchors.fill: parent

        Label {
            id: lblNFCSupported
            visible: !NFCManager.isNFCSupported
            anchors.centerIn:parent
            width: parent.width
            height: parent.height*0.10
            text: NFCManager.supportedMessage
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: "white"
        }
        Label {
            id: lblNFCAvailable
            visible: NFCManager.isNFCSupported && !NFCManager.isNFCAvailable
            anchors.centerIn:parent
            width: parent.width
            height: parent.height*0.10
            text: NFCManager.nfcNotAvailableMessage
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: "white"
        }
        Label {
            id: lblNFCStartDetection
            visible: NFCManager.isNFCAvailable && NFCManager.targetDetecting
            anchors.centerIn:parent
            width: parent.width
            height: parent.height*0.10
            text: NFCManager.targetDetectingMessage
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: "white"
        }

    }

    Item{
        id:targetFoundItem
        visible: NFCManager.targetConnected
        anchors.fill: parent
        Label {
            id: trgtConnectedLbl
            anchors.top:parent.top
            width: parent.width
            height: parent.height*0.10
            text: "Tag Connected"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: "white"
        }
        Label {
            id: trgtUIDLbl
            anchors.top:trgtConnectedLbl.bottom
            width: parent.width
            height: parent.height*0.10
            text: NFCManager.targetUID
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: "white"
        }
        Label {
            id: trgtType
            anchors.top:trgtUIDLbl.bottom
            width: parent.width
            height: parent.height*0.10
            text: NFCManager.targetType
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: "white"
        }
        Label {
            id: trgtAccesMethod
            anchors.top:trgtType.bottom
            width: parent.width
            height: parent.height*0.10
            text: NFCManager.targetAccessMethod
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: "white"
        }
        Label {
            id: trgtError
            anchors.top:trgtAccesMethod.bottom
            width: parent.width
            height: parent.height*0.10
            text: NFCManager.targetError
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: "white"
        }

     }

}

