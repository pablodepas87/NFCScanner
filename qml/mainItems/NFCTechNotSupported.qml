import QtQuick 2.0
import QtQuick.Controls 2.14
Item {
   anchors.fill: parent
   visible: false
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

}
