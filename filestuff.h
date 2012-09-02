#ifndef FILESTUFF_H
#define FILESTUFF_H

#include <QString>

class filestuff
{
public:
    filestuff();
    QStringList listFiles(QString directory, QString filter, QString sort, bool reversed);
    QString mcDir();
    QString appDir();
    QString getOS();
    bool exMake(QString path);
    void removeDir(QString dirName);
    void copyDir(QString src, QString dest);
};

#endif // FILESTUFF_H
