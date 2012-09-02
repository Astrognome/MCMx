#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QVariant>

class settings
{
public:
    settings();
    QVariant read(QString group, QString key, QVariant fallback);
    bool write(QString group, QString key, QVariant value);
};

#endif // SETTINGS_H
