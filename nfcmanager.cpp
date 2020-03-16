#include "nfcmanager.h"
#include <QDebug>
#include <QNdefMessage>
#include <QNdefNfcTextRecord>

static const int nfcScanAvailableTimerDuration = 2000;

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

   connect(nfcManger,&QNearFieldManager::targetDetected,this,&NFCManager::targetDetected);
   connect(nfcManger,&QNearFieldManager::targetLost,this,&NFCManager::targetLost);
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

QByteArray NFCManager::targetUID() const
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

QNdefMessage NFCManager::ndefMessage() const
{
    QNdefNfcTextRecord txtRecord;
    txtRecord.setText("Hello World");
    return QNdefMessage(txtRecord);

}

QNdefMessage NFCManager::emptyNdefMessage() const
{
    QNdefMessage nDefMessage;
    QNdefRecord nullRecord;
    nullRecord.setTypeNameFormat(QNdefRecord::Empty);
    nDefMessage.append(nullRecord);
    nDefMessage.append(nullRecord);
    return nDefMessage;
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

 //    if (isNFCAvailable() != nfcManger->isAvailable()) {
       setNFCAvailable(nfcManger->isAvailable());
       if (isNFCAvailable()){
        // start to detected nfc target
        nfcManger->setTargetAccessModes(QNearFieldManager::NdefWriteTargetAccess);
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
//    }
}

void NFCManager::targetDetected(QNearFieldTarget *target)
{
    connect(target,&QNearFieldTarget::requestCompleted, this, &NFCManager::readRequest);
    connect(target,&QNearFieldTarget::ndefMessageRead, this, &NFCManager::readMemoryBlock);
    connect(target,&QNearFieldTarget::ndefMessagesWritten, this, &NFCManager::ndefMessageWritten);
    connect(target,&QNearFieldTarget::error, this, &NFCManager::setTargetError);

    m_targetConnected = true;
    emit targetConnectedChanged();

    // the uid into st25 app is reverse respect to target->uid so i reversed it
    QByteArray uid(target->uid());
    std::reverse(uid.begin(),uid.end());

    setTargetUID(uid.toHex(' ').toUpper());
    setTargetAccessMethod(target->accessMethods());
    setTargetType(target->type());

    m_request = target->writeNdefMessages(QList<QNdefMessage>() << ndefMessage());
    if (!m_request.isValid())
       setTargetError(QNearFieldTarget::NdefWriteError, m_request);
    // readNdefMessage
    m_request = target->readNdefMessages();
    if (!m_request.isValid())
       setTargetError(QNearFieldTarget::NdefReadError, m_request);

    // erase ndefmessage
    m_request = target->writeNdefMessages(QList<QNdefMessage>() << emptyNdefMessage());
    if (!m_request.isValid())
       setTargetError(QNearFieldTarget::NdefWriteError, m_request);

    m_request = target->sendCommand(readCommand());
    QByteArray response = target->requestResponse(m_request).toByteArray();
    qDebug() << response.toHex(' ').data();


    m_request = target->sendCommand(writeCommand());
    if (!m_request.isValid())
        setTargetError(QNearFieldTarget::CommandError, m_request);
    response = target->requestResponse(m_request).toByteArray();
    qDebug() << response.toHex(' ').data();
}

void NFCManager::targetLost(QNearFieldTarget *target)
{
    m_targetConnected = false;
    emit targetConnectedChanged();

    setTargetUID("");
    target->deleteLater();
}

void NFCManager::setTargetUID(QByteArray targetUID)
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
         m_targetType = "NFC tag type 5 target";
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
     case QNearFieldTarget::NdefAccess |  QNearFieldTarget::TagTypeSpecificAccess:
          m_targetAccessMethod = "NdefAccess & TagTypeSpecifAccess";
          break;
    default:
          m_targetAccessMethod = "AccessMethod unefined";
          break;
    }

    emit targetAccessMethodschanged();
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
        case QNearFieldTarget::CommandError:
            m_targetError = "Failed to send a command to the target.";
            break;
        default:
            m_targetError = "Unknown error";
        }

        emit targetErrochanged();
}

void NFCManager::readMemoryBlock(const QNdefMessage &msg)
{
    /*A QNdefMessage is a collection of 0 or more QNdefRecords.
     * QNdefMessage inherits from QList<QNdefRecord> and
     * therefore the standard QList functions can be used to manipulate
     * the NDEF records in the message.*/

    for (const QNdefRecord &record : msg){
        if ( record.isRecordType<QNdefNfcTextRecord>()){
           QNdefNfcTextRecord textRecord(record);
           qDebug() << textRecord.text();
        }
    }

    // After read ndefMessage i must erase it and test is completed
    nfcManger->setTargetAccessModes(QNearFieldManager::NdefWriteTargetAccess);
}

void NFCManager::ndefMessageWritten()
{
   nfcManger->setTargetAccessModes(QNearFieldManager::NdefReadTargetAccess);
}

void NFCManager::readRequest(const QNearFieldTarget::RequestId &id)
{
    Q_UNUSED(id)
}

QByteArray NFCManager::readCommand()
{
    /* more info pag.84 datasheet*/

    QByteArray readCommand;

    readCommand.append(0x02);   // REQUEST FLAG CONFIG 0010 0000 (big endian) put the tag in Quiet state
    readCommand.append(0x20);   // Read single block command
    readCommand.append(0x01);   // block number no big endian

    return readCommand;
}

QByteArray NFCManager::writeCommand()
{
    /* more info pag.86 datasheet ST25DV04K-I*/

    QByteArray writeCommand;

    writeCommand.append(0x02);   // REQUEST FLAG CONFIG 0010 0000 (big endian) put the tag in Quiet state
    writeCommand.append(0x21);   // Write single block command
    writeCommand.append(0x01);   // block number no big endian
    writeCommand.append(0xFF);   // START DATA first byte of the block
    writeCommand.append(0xFF);
    writeCommand.append(0xFF);
    writeCommand.append(0xFF);   // ENDA DATA LAST byte of the block ( 1 block is 4 byte )

    return writeCommand;
}
