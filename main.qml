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

