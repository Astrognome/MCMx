#include "worldbackup.h"
#include "filestuff.h"
#include "settings.h"
#include "general.h"
#include "mainwindow.h"

#include <QString>
#include <QStringList>
#include <QDir>
#include <QSettings>
#include <QDateTime>

filestuff fs;

worldbackup::worldbackup()
{
}

QString worldbackup::parseWorld(QString world)
{
    world.remove("[deleted] ");
    return world;
}


QStringList worldbackup::listWorlds()
{
    QStringList result(fs.listFiles(fs.mcDir() + "/saves","folders","",false));
    QStringList backupWorlds(fs.listFiles(fs.appDir() + "/backups","folders","",false));
        for (int i = 0; i < backupWorlds.count(); i++){
        if (!result.contains(backupWorlds[i])){
            result.append("[deleted] " + backupWorlds[i]);
            worldConf_Write(backupWorlds[i], "deleted", true);
        }
    }


    return result;
}

QStringList worldbackup::listBackups(QString world)
{
    if (worldConf_Read(world, "deleted", false).toBool()){
        world = parseWorld(world);
    }
    QStringList list(fs.listFiles(fs.appDir() + "/backups/" + world,
                                    "both","",false));
    QStringList result;
    //remove stuff from list
    for (int i = 0; i < list.count(); i++){
        if (list.at(i) != "config.ini"){
            result.append(list[i]);
        }
    }
    return result;
}

void worldbackup::createBackupData(QString world)
{
    QString worldDir(fs.appDir() + "/backups/" + world);
    fs.exMake(worldDir);
    //write default values to config
    //QSettings worldSettings(worldDir + "/config.ini", QSettings::IniFormat);
}

void worldbackup::worldConf_Write(QString world, QString key, QVariant value)
{
    if (world.contains("[deleted] ")){
        world.remove("[deleted] ");
    }
    QString worldDir(fs.appDir() + "/backups/" + world);
    QSettings worldSettings(worldDir + "/config.ini", QSettings::IniFormat);
    worldSettings.setValue(key, value);
}

QVariant worldbackup::worldConf_Read(QString world, QString key, QVariant fallback)
{
    if (world.contains("[deleted] ")){
        world.remove("[deleted] ");
    }
    QString worldDir(fs.appDir() + "/backups/" + world);
    QSettings worldSettings(worldDir + "/config.ini", QSettings::IniFormat);
    return worldSettings.value(key, fallback);
}

void worldbackup::createBackup(QString world)
{
    QString worldDir(fs.mcDir() + "/saves/" + world);
    QString backDir(fs.appDir() + "/backups/" + world);
    QString savesDir(fs.mcDir() + "/saves");
    QDateTime currentTime(QDateTime::currentDateTime());
    QString timeString(currentTime.toString("[yyyy-MM-dd] hh-mm-ss"));
    backDir = backDir + "/" + timeString;
    if (!worldConf_Read(world, "compression/enabled", false).toBool()){
        fs.copyDir(worldDir, backDir);
    } else if (worldConf_Read(world, "compression/enabled", false).toBool()){
        QString compCmd(worldConf_Read(world, "compression/compresscmd", "none").toString());
        if (compCmd == "none"){
            general gen;
            gen.showMessage("Compression Invalid!","","y");
        } else {
            compCmd.replace("!saves", savesDir);
            compCmd.replace("!backup", backDir);
            compCmd.replace("!world", worldDir);
            compCmd.replace("!worldname", world);
            compCmd.replace("!backups", fs.appDir() + "/backups");
            system(compCmd.toAscii());
        }
    }
}

void worldbackup::removeBackup(QString world, QString backup)
{
    QString backDir(fs.appDir() + "/backups/" + world);
    if (!worldConf_Read(world, "compression/enabled", false).toBool()){
        fs.removeDir(backDir + "/" + backup);
    } else {
        QFile::remove(backDir + "/" + backup);
    }
}

void worldbackup::restoreBackup(QString world, QString backup)
{
    general gen;
    QString backDir(fs.appDir() + "/backups/" + world);
    QString bd(backDir + "/" + backup);
    QString worldDir(fs.mcDir() + "/saves/" + world);
    QString savesDir(fs.mcDir() + "/saves");
    int doRestore = gen.showMessage("Restore World?", "This will replace your world with the selected backup", "yn");
    if (doRestore == 1){
        fs.removeDir(worldDir);
        if (!worldConf_Read(world, "compression/enabled", false).toBool()){
            fs.copyDir(bd, worldDir);
        } else if (worldConf_Read(world, "compression/enabled", false).toBool()){
            QString restCmd(worldConf_Read(world, "compression/restorecmd", "none").toString());
            if (restCmd == "none"){
                general gen;
                gen.showMessage("Compression Invalid!","","y");
            } else {
                restCmd.replace("!backup", bd);
                restCmd.replace("!saves", savesDir);
                restCmd.replace("!world", worldDir);
                restCmd.replace("!worldname", world);
                restCmd.replace("!backups", fs.appDir() + "/backups");
                system(restCmd.toAscii());
            }
        }
    }
}


void worldbackup::compApply(QString world, QString cmd1, QString cmd2, bool enabled)
{
    worldConf_Write(world, "compression/enabled", enabled);
    worldConf_Write(world, "compression/compresscmd", cmd1);
    worldConf_Write(world, "compression/restorecmd", cmd2);
}
