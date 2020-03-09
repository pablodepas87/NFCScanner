#include "nfcmanager.h"
#include <QDebug>

static const int nfcScanAvailableTimerDuration = 5000;

NFCManager::NFCManager(QObject *parent) : QObject(parent)
    ,m_isNFCSupported {false}
    ,m_isNFCAvailable {false}
    ,m_supportedMessage {"The device doesn't support NFC technology"}
    ,m_nfcNotAvailableMessage {"NFC not available.Enabled it on device settings"}
    ,m_targetDetectingMessage {"Move the device to NFC target "}
    ,m_targetDetecting {false}
    ,m_targetConnected {false}
    ,m_targetUID {""}
    ,m_targetAccessMethod {""}
    ,m_targetType{""}
    ,m_targetError{""}
{
   // To detect if the device has NFC technology
   m_isNFCSupported = nfcManger->isSupported();
   emit isNFCSupportedChanged();

   // if NFC is available start target detection
   scanNFCAvailablety();

   // scan NFC status each 30s
   connect(nfcAvailableTimer,SIGNAL(timeout()),this,SLOT(scanNFCAvailablety()));
   nfcAvailableTimer->start(nfcScanAvailableTimerDuration);

   connect(nfcManger,SIGNAL(targetDetected()),this,SLOT(targetDetected()));
   connect(nfcManger,SIGNAL(targetLost()),this,SLOT(targetLost()));
}

bool NFCManager::isNFCsupported() const
{
    return m_isNFCSupported;
}

bool NFCManager::isNFCAvailable() const
{
    return m_isNFCAvailable;
}

bool NFCManager::targetDetecting() const
{
    return m_targetDetecting;
}

bool NFCManager::targetConnected() const
{
    return m_targetConnected;
}

QString NFCManager::targetUID() const
{
    return m_targetUID;
}

QString NFCManager::targetAccessMethod() const
{
    return m_targetAccessMethod;
}

QString NFCManager::targetType() const
{
    return m_targetType;
}

QString NFCManager::targetError() const
{
    return m_targetError;
}

void NFCManager::setNFCAvailable(bool isNFCAvailable)
{
    if (m_isNFCAvailable == isNFCAvailable)
        return;

    m_isNFCAvailable = isNFCAvailable;
    emit isNFCAvailableChanged();
}

void NFCManager::scanNFCAvailablety()
{
    // SCAN if the NFC of the device is active or not

    if (isNFCAvailable() != nfcManger->isAvailable()) {
       setNFCAvailable(nfcManger->isAvailable());
       if (isNFCAvailable()){

        // start to detected nfc target
        nfcManger->setTargetAccessModes(QNearFieldManager::NdefReadTargetAccess);
        m_targetDetecting = nfcManger->startTargetDetection();
        emit targetDetectingChanged();

       }
       else{

        // stop to detected nfc target because NFC is not available
        nfcManger->setTargetAccessModes(QNearFieldManager::NoTargetAccess);
        nfcManger->stopTargetDetection();
        m_targetDetecting = false;
        emit targetDetectingChanged();

       }
    }
}

void NFCManager::targetDetected(QNearFieldTarget *target)
{

    connect(target,SIGNAL(error), this, SLOT(setTargetError()));

    m_targetConnected = true;

    setTargetUID(QString::fromStdString(target->uid().toStdString()));
    setTargetAccessMethod(target->accessMethods());
    setTargetType(target->type());

    emit targetConnectedChanged();
}

void NFCManager::targetLost(QNearFieldTarget *target)
{
    m_targetConnected = false;
    emit targetConnectedChanged();

    setTargetUID("");
    target->deleteLater();
}

void NFCManager::setTargetUID(QString targetUID)
{
    if (m_targetUID == targetUID)
        return;

    m_targetUID = targetUID;
    emit targetUIDchanged();
}

void NFCManager::setTargetType(QNearFieldTarget::Type typeTarget)
{
    switch (typeTarget){

    case QNearFieldTarget::ProprietaryTag:
         m_targetType = "unidentified proprietary target tag";
         break;
    case QNearFieldTarget::NfcTagType1:
         m_targetType = "NFC tag type 1 target.";
         break;
    case QNearFieldTarget::NfcTagType2:
         m_targetType = "NFC tag type 2 target.";
         break;
    case QNearFieldTarget::NfcTagType3:
         m_targetType = "NFC tag type 3 target.";
         break;
    case QNearFieldTarget::NfcTagType4:
         m_targetType = "NFC tag type 4 target.";
         break;
    case QNearFieldTarget::MifareTag:
         m_targetType = "Mifare target";
         break;
    default:
         m_targetType = "undefined";
         break;
    }

    emit targetTypechanged();

}

void NFCManager::setTargetAccessMethod(QNearFieldTarget::AccessMethods accessMethod)
{
    switch (accessMethod) {

     case QNearFieldTarget::UnknownAccess:
          m_targetAccessMethod = "The target supports an unknown access type.";
          break;
     case QNearFieldTarget::NdefAccess:
          m_targetAccessMethod = "The target supports NDEF messages using readNdefMessages() and writeNdefMessages().";
          break;
     case QNearFieldTarget::TagTypeSpecificAccess:
          m_targetAccessMethod = "The target supports sending tag type specific commands using sendCommand() and sendCommands().";
          break;
     case QNearFieldTarget::LlcpAccess:
          m_targetAccessMethod = "The target supports peer-to-peer LLCP communication.";
          break;
    default:
          m_targetAccessMethod = "";
          break;
    }


}

void NFCManager::setTargetError(QNearFieldTarget::Error error, const QNearFieldTarget::RequestId &id)
{
    Q_UNUSED(error);
    Q_UNUSED(id);

    switch (error) {
        case QNearFieldTarget::NoError:
            m_targetError = "";
            break;
        case QNearFieldTarget::UnsupportedError:
            m_targetError = "Unsupported tag";
            break;
        case QNearFieldTarget::TargetOutOfRangeError:
            m_targetError = "Tag removed from field";
            break;
        case QNearFieldTarget::NoResponseError:
            m_targetError = "No response from tag";
            break;
        case QNearFieldTarget::ChecksumMismatchError:
            m_targetError = "Checksum mismatch";
            break;
        case QNearFieldTarget::InvalidParametersError:
            m_targetError = "Invalid parameters";
            break;
        case QNearFieldTarget::NdefReadError:
            m_targetError = "NDEF read error";
            break;
        case QNearFieldTarget::NdefWriteError:
            m_targetError = "NDEF write error";
            break;
        default:
            m_targetError = "Unknown error";
        }

        emit targetErrochanged();
        nfcManger->setTargetAccessModes(QNearFieldManager::NoTargetAccess);
        nfcManger->stopTargetDetection();

}
