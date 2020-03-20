import QtQuick 2.14
import QtQuick.Controls 2.2
import QtQuick.Window 2.12
import "./mainItems"
ApplicationWindow {
    visible: true
    width: Screen.width
    height: Screen.height
    property bool portaitMode: Screen.desktopAvailableHeight > Screen.desktopAvailableWidth

    background: Rectangle{
          color: "#166ab3"
    }

    Item {
       anchors.fill: parent

       states: [
           State {
               when: !NFCManager.isNFCSupported
               PropertyChanges {
                   target: nfcNotSupported
                   visible: true
               }
           },
           State {
               when: NFCManager.isNFCSupported
               PropertyChanges {
                   target: nfcSupported
                   visible: true
               }
           }
       ]

       NFCTechNotSupported {
           id:nfcNotSupported
       }

       NFCTechSupported {
           id:nfcSupported
       }

    }


}

