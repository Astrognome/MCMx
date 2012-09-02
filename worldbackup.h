#ifndef WORLDBACKUP_H
#define WORLDBACKUP_H

#include <QString>
#include <QVariant>

class worldbackup
{
public:
    worldbackup();
    QStringList listWorlds();
    QStringList listBackups(QString world);
    void createBackupData(QString world);
    void createBackup(QString world);
    void removeBackup(QString world, QString backup);
    void restoreBackup(QString world, QString backup);
    void worldConf_Write(QString world, QString key, QVariant value);
    QVariant worldConf_Read(QString world, QString key, QVariant value, QVariant fallback);
};

#endif // WORLDBACKUP_H
