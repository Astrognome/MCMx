#ifndef FILESTUFF_H
#define FILESTUFF_H

#include <QString>

class filestuff
{
public:
    filestuff();
    static QStringList listFiles(QString directory, QString filter, QString sort, bool reversed);
    static QString mcDir();
    static QString appDir();
    static QString getOS();
    static bool exMake(QString path);
    static void removeDir(QString dirName);
    static void copyDir(QString src, QString dest);
};

#endif // FILESTUFF_H
