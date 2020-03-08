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
    target->uid();
}

void NFCManager::targetLost(QNearFieldTarget *target)
{
    target->deleteLater();
}
