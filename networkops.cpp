#include "networkops.h"

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QWaitCondition>
#include <QEventLoop>
#include <QIODevice>
#include <QFile>

networkops::networkops(QObject *parent) :
    QObject(parent)
{

}

bool networkops::downloadFile(QUrl url, QString path)
{
    QFile destFile(path);
    QNetworkRequest request(url);
    QNetworkReply* reply = qnam.get(request);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    destFile.open(QIODevice::WriteOnly);
    destFile.write(reply->readAll());
    true;
}
