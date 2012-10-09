#ifndef NETWORKOPS_H
#define NETWORKOPS_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>

class networkops : public QObject
{
    Q_OBJECT
public:
    explicit networkops(QObject *parent = 0);
    
signals:
    
public slots:
    bool downloadFile(QUrl url, QString path);
private:
    QNetworkAccessManager qnam;
    
};

#endif // NETWORKOPS_H
