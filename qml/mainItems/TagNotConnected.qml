import QtQuick 2.0
import QtQuick.Controls 2.14

Item {
    width: parent.width
    height: parent.height * 0.94
    anchors.bottom: parent.bottom
    visible: false

    Image {
       source: NFCManager.isNFCAvailable ? "qrc:/nfcFounding.png" : "qrc:/nfc_off.png"
       anchors.horizontalCenter: parent.horizontalCenter
       width: portaitMode ? sourceSize.width *0.60 : sourceSize.width * 0.30
       height: portaitMode ? sourceSize.height*0.60 : sourceSize.height * 0.30
       anchors.top: parent.top
       anchors.topMargin: parent.height * 0.10

       SequentialAnimation on opacity {
           running: NFCManager.isNFCAvailable
           loops: Animation.Infinite
           alwaysRunToEnd: true
           PropertyAnimation {
               from: true
               to: false
               duration: 1000
           }
           PropertyAnimation {
               from: false
               to: true
               duration: 1000
           }
       }
    }

    Label {
        id: lblNFCAvailable
        visible: NFCManager.isNFCSupported && !NFCManager.isNFCAvailable
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 0.30
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.95
        height: parent.height * 0.10
        text: NFCManager.nfcNotAvailableMessage
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: "white"
        font.pixelSize: 30
        font.capitalization: Font.AllUppercase
        fontSizeMode: Text.Fit
    }
    Label {
        id: lblNFCStartDetection
        visible: NFCManager.isNFCAvailable && NFCManager.targetDetecting
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 0.30
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.95
        height: parent.height*0.10
        text: NFCManager.targetDetectingMessage
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: "white"
        font.pixelSize: 30
        font.capitalization: Font.AllUppercase
        fontSizeMode: Text.Fit
    }
}
