#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QVariant>
#include <QSettings>

class settings
{
public:
    settings();
    QVariant read(QString group, QString key, QVariant fallback);
    bool write(QString group, QString key, QVariant value);
private:
    QSettings stfile;
};

#endif // SETTINGS_H
