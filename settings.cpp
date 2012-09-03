#include "settings.h"
#include "filestuff.h"

#include <QSettings>
#include <QString>
#include <QDir>

//QSettings stfile(QSettings::IniFormat, QSettings::UserScope, "MCMx", "Config");

//QSettings stfile(QString(filestuff::appDir() + "/Config.ini"), QSettings::IniFormat);

QSettings stfile(QDir::currentPath() + "/Config.ini", QSettings::IniFormat);

settings::settings()
{

}

QVariant settings::read(QString group, QString key, QVariant fallback)
{
    stfile.beginGroup(group);
    QVariant result = stfile.value(key, fallback);
    stfile.endGroup();
    return result;
}

bool settings::write(QString group, QString key, QVariant value)
{
    try {
        stfile.beginGroup(group);
        stfile.setValue(key, value);
        stfile.endGroup();
        return true;
    }
    catch (...){
        return false;
    }
}
