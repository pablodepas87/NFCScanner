import QtQuick 2.14
import "../objects"
Item {
    anchors.fill: parent
    states: [
        State {
            when: NFCManager.targetConnected
            PropertyChanges {
                target: tagConnected
                visible: true
            }
        },
        State {
            when: !NFCManager.targetConnected
            PropertyChanges {
                target: tagNotConnected
                visible: true
            }
        }
    ]

    TagConnectionState{
        id:connectionState
    }

    TagConnected{
        id:tagConnected
    }

    TagNotConnected {
       id:tagNotConnected
    }

}
