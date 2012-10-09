#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>
#include <QString>

class launcher : public QObject
{
    Q_OBJECT
public:
    explicit launcher(QObject *parent = 0);
    void downloadLauncher();

    QString launcherPath();
signals:
    void pushStatus(QString);
};

#endif // LAUNCHER_H
