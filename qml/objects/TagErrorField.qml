import QtQuick 2.0
import QtQuick.Controls 2.14

Rectangle {

  width: parent.width * 0.95
  height: parent.height *0.30
  anchors.horizontalCenter: parent.horizontalCenter
  radius: 2
  visible: NFCManager.targetError != "" ? true : false
  Image{
      source: "qrc:/error.png"
      width: portaitMode ? sourceSize.width *0.40 : sourceSize.width * 0.20
      height: portaitMode ? sourceSize.height * 0.40 : sourceSize.height * 0.20
      anchors.horizontalCenter: parent.horizontalCenter
      anchors.top: parent.top
      anchors.topMargin: parent.height * 0.05
  }

  Label {
      id: trgtError
      anchors.bottom: parent.bottom
      anchors.bottomMargin: parent.height *0.02
      anchors.horizontalCenter: parent.horizontalCenter
      width: parent.width * 0.95
      height: parent.height * 0.40
      text: NFCManager.targetError
      verticalAlignment: Text.AlignVCenter
      horizontalAlignment: Text.AlignHCenter
      color: "black"
      fontSizeMode: Text.Fit
      minimumPixelSize: 15
      font.pixelSize: 22
      font.bold: true
      font.capitalization: Font.AllUppercase

  }
}
