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
public:

    explicit NFCManager(QObject *parent = nullptr);

    bool isNFCsupported() const;
    bool isNFCAvailable() const;

    bool targetDetecting() const;

public slots:

    void setNFCAvailable(bool isNFCAvailable);
    void scanNFCAvailablety();
    void targetDetected(QNearFieldTarget *target);
    void targetLost(QNearFieldTarget *target);

signals:

    void isNFCSupportedChanged();
    void isNFCAvailableChanged();
    void targetDetectingChanged();

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
};

#endif // NFCMANAGER_H
