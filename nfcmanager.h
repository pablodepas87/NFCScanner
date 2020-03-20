#ifndef NFCMANAGER_H
#define NFCMANAGER_H

#include <QObject>
#include <QNearFieldManager>
#include <QNearFieldTarget>
#include <QTimer>

class NFCManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isNFCSupported READ isNFCsupported  NOTIFY isNFCSupportedChanged)
    Q_PROPERTY(bool isNFCAvailable READ isNFCAvailable  WRITE setNFCAvailable NOTIFY isNFCAvailableChanged)
    Q_PROPERTY(bool targetDetecting READ targetDetecting NOTIFY targetDetectingChanged)
    Q_PROPERTY(QString supportedMessage MEMBER m_supportedMessage CONSTANT )
    Q_PROPERTY(QString nfcNotAvailableMessage  MEMBER m_nfcNotAvailableMessage CONSTANT )
    Q_PROPERTY(QString targetDetectingMessage  MEMBER m_targetDetectingMessage CONSTANT )
    Q_PROPERTY(bool targetConnected READ targetConnected  NOTIFY targetConnectedChanged)
    Q_PROPERTY(QByteArray targetUID READ targetUID WRITE setTargetUID NOTIFY  targetUIDchanged)
    Q_PROPERTY(QString targetAccessMethod READ targetAccessMethod NOTIFY targetAccessMethodschanged)
    Q_PROPERTY(QString targetType READ targetType NOTIFY targetTypechanged )
    Q_PROPERTY(QString targetError READ targetError NOTIFY targetErrochanged)
    Q_PROPERTY(int operationCount READ operationCount NOTIFY operationCountchanged)
    Q_PROPERTY(bool testBlockWrited READ testBlockWrited NOTIFY testBlockWritedchanged )
    Q_PROPERTY(bool testBlockReset READ testBlockReset NOTIFY testBlockResetchanged )
    Q_PROPERTY(QByteArray dataWrited READ dataWrited NOTIFY dataWritedchanged )

public:

    explicit NFCManager(QObject *parent = nullptr);

    bool isNFCsupported() const;
    bool isNFCAvailable() const;
    bool targetDetecting() const;
    bool targetConnected() const;
    QByteArray targetUID() const;
    QString targetAccessMethod() const;
    QString targetType() const;
    QString targetError() const;
    QNdefMessage ndefMessage() const;
    QNdefMessage emptyNdefMessage() const;
    bool UseNFCTextMessage() const;
    int operationCount() const;
    bool testBlockWrited() const;
    bool testBlockReset() const;

    QByteArray dataWrited() const;

public slots:

    void setNFCAvailable(bool isNFCAvailable);
    void scanNFCAvailablety();
    void targetDetected(QNearFieldTarget *target);
    void targetLost(QNearFieldTarget *target);
    void setTargetUID(QByteArray targetUID);
    void setTargetType(QNearFieldTarget::Type typeTarget);
    void setTargetAccessMethod(QNearFieldTarget::AccessMethods accessMethod);
    void setTargetError(QNearFieldTarget::Error error, const QNearFieldTarget::RequestId &id);
    void readMemoryBlock(const QNdefMessage &msg);
    void ndefMessageWritten();
    void readRequest(const QNearFieldTarget::RequestId &id);
    void setUseNFCTextMessage(bool UseNFCTextMessage);
    void infoTag(QNearFieldTarget *target);


signals:

    void isNFCSupportedChanged();
    void isNFCAvailableChanged();
    void targetDetectingChanged();
    void targetConnectedChanged();
    void targetUIDchanged();
    void targetAccessMethodschanged();
    void targetTypechanged();
    void targetErrochanged();
    void operationCountchanged();
    void writeBlockOkchanged();
    void testBlockWritedchanged();
    void testBlockResetchanged();
    void dataWritedchanged(QByteArray dataWrited);

private:

    QByteArray readCommand();
    QByteArray writeCommand();
    QByteArray resetBlockCommand();
    void dataToWrite();
    char charToWrite(int pos);

    QNearFieldManager *nfcManger = new QNearFieldManager(this);
    QNearFieldTarget::RequestId  m_request ;
    bool m_isNFCSupported;
    bool m_isNFCAvailable;
    QString m_supportedMessage;
    QString m_nfcNotAvailableMessage;
    QString m_targetDetectingMessage;
    QTimer *nfcAvailableTimer = new QTimer();
    bool m_targetDetecting;
    bool m_targetConnected;
    QByteArray m_targetUID;
    QString m_targetAccessMethod;
    QString m_targetType;
    QString m_targetError;
    bool m_UseNFCTextMessage;
    QByteArray blockMemoryToWrite;
    QByteArray nullArray ;
    int m_operationCount;
    bool m_writeBlockOK;
    bool m_testBlockWrited;
    bool m_testBlockReset;

};

#endif // NFCMANAGER_H
