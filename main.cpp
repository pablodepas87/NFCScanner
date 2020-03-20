#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "nfcmanager.h"
#include <QQmlContext>
#include <QDebug>
#include <QtAndroid>
#include <QByteArray>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    NFCManager nfcManager;
    engine.rootContext()->setContextProperty("NFCManager",&nfcManager);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);

    #ifdef Q_OS_ANDROID
     // the splashscreen is customizable with androidManifest.xml
     QtAndroid::hideSplashScreen(100);
    #endif
    return app.exec();
}
