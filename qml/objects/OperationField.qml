import QtQuick 2.0

Rectangle{
  property string operationName:  ""
  property string operationValue: ""
  property alias  fieldValue: fieldValue
  width: parent.width * 0.95
  height: parent.height * 0.10
  anchors.horizontalCenter: parent.horizontalCenter
  border.color: "white"
  border.width: 0
  radius: 2
  color: "#6699CC"
  Rectangle {
     id: fieldName
     width: parent.width - ( parent.border.width * 2)
     height: parent.height * 0.50
     anchors.horizontalCenter: parent.horizontalCenter
     radius: 2
     color: "transparent"
     Rectangle{
         width: parent.width
         height: parent.radius
         color: parent.color
         anchors.bottom: parent.bottom
     }

     Text {
        anchors.fill: parent
        text: operationName
        fontSizeMode: Text.Fit
        font.pixelSize: 20
        minimumPixelSize: 15
        color: "white"
        font.capitalization: Font.AllUppercase
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
     }
  }

  Rectangle {
     id:fieldValue
     width: parent.width - ( parent.border.width * 2)
     height: parent.height * 0.50
     anchors.horizontalCenter: parent.horizontalCenter
     anchors.bottom: parent.bottom
     radius: 2
     color: "transparent"
     Rectangle{
         width: parent.width
         height: parent.radius
         color: parent.color
         anchors.top: parent.top
     }

     Text {
        anchors.fill: parent
        text: operationValue
        fontSizeMode: Text.Fit
        font.pixelSize: 20
        minimumPixelSize: 15
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.capitalization: Font.AllUppercase
     }

  }
}
