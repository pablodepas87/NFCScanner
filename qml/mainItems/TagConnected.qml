import QtQuick 2.0
import QtQuick.Controls 2.14
import "../objects"
Item {
    width: parent.width
    height: parent.height * 0.92
    anchors.bottom: parent.bottom
    visible: false

    InfoTagRow{
        id: trgtUIDLbl
        lblName: "NFC UID"
        lblValue: NFCManager.targetUID
        anchors.top:parent.top
        anchors.topMargin: parent.height * 0.02
    }

    InfoTagRow{
        id: trgtType
        lblName: "NFC TYPE"
        lblValue: NFCManager.targetType
        anchors.top:trgtUIDLbl.bottom
        anchors.topMargin: parent.height * 0.02
    }

    InfoTagRow{
        id: trgtAccesMethod
        lblName: "NFC A.M."
        lblValue: NFCManager.targetAccessMethod
        anchors.top:trgtType.bottom
        anchors.topMargin: parent.height * 0.02
    }

    OperationField{
        id:writeOperationField
        fieldValue.color: NFCManager.testBlockWrited ? "#6ee387" : "#ff6347"
        anchors.top: trgtAccesMethod.bottom
        anchors.topMargin: parent.height * 0.02
        operationName: "WRITE BLOCK 1"
    }

    OperationField{
        id:resetOperationField
        fieldValue.color: NFCManager.testBlockReset ? "#6ee387" : "#ff6347"
        anchors.top: writeOperationField.bottom
        anchors.topMargin: parent.height * 0.02
        operationName: "RESET BLOCK 1"
        operationValue: "00 00 00 00"
    }

    OperationField{
        id:operationCountField
        fieldValue.color: NFCManager.operationCount == 4 ? "#6ee387" : "#ff6347"
        anchors.top: resetOperationField.bottom
        anchors.topMargin: parent.height * 0.02
        operationName: "TOTAL OPERATION "
        operationValue: NFCManager.operationCount
    }

    TagErrorField{
        anchors.top: operationCountField.bottom
        anchors.topMargin: parent.height * 0.02
    }

    Connections {
        target: NFCManager
        onDataWritedchanged: {
           writeOperationField.operationValue = dataWrited
        }
    }
}
