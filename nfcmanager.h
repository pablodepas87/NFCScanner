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
    Q_PROPERTY(bool targetConnected READ targetConnected NOTIFY targetConnectedChanged)
    Q_PROPERTY(QString targetUID READ targetUID WRITE setTargetUID NOTIFY  targetUIDchanged)
    Q_PROPERTY(QString targetAccessMethod READ targetAccessMethod NOTIFY targetAccessMethodschanged)
    Q_PROPERTY(QString targetType READ targetType NOTIFY targetTypechanged )
    Q_PROPERTY(QString targetError READ targetError NOTIFY targetErrochanged)

public:

    explicit NFCManager(QObject *parent = nullptr);

    bool isNFCsupported() const;
    bool isNFCAvailable() const;
    bool targetDetecting() const;
    bool targetConnected() const;
    QString targetUID() const;
    QString targetAccessMethod() const;
    QString targetType() const;
    QString targetError() const;

public slots:

    void setNFCAvailable(bool isNFCAvailable);
    void scanNFCAvailablety();
    void targetDetected(QNearFieldTarget *target);
    void targetLost(QNearFieldTarget *target);
    void setTargetUID(QString targetUID);
    void setTargetType(QNearFieldTarget::Type typeTarget);
    void setTargetAccessMethod(QNearFieldTarget::AccessMethods accessMethod);
    void setTargetError(QNearFieldTarget::Error error, const QNearFieldTarget::RequestId &id);

signals:

    void isNFCSupportedChanged();
    void isNFCAvailableChanged();
    void targetDetectingChanged();
    void targetConnectedChanged();
    void targetUIDchanged();
    void targetAccessMethodschanged();
    void targetTypechanged();
    void targetErrochanged();

private:

    QNearFieldManager *nfcManger = new QNearFieldManager(this);
    QNearFieldTarget  *nfcTarget;
    bool m_isNFCSupported;
    bool m_isNFCAvailable;
    QString m_supportedMessage;
    QString m_nfcNotAvailableMessage;
    QString m_targetDetectingMessage;
    QTimer *nfcAvailableTimer = new QTimer();
    bool m_targetDetecting;
    bool m_targetConnected;
    QString m_targetUID;
    QString m_targetAccessMethod;
    QString m_targetType;
    QString m_targetError;
};

#endif // NFCMANAGER_H
