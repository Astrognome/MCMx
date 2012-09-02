#include "filestuff.h"
#include "settings.h"

#include <QString>
#include <QStringList>
#include <QDir>
#include <QFile>

settings st;

filestuff::filestuff()
{
}

QString filestuff::getOS()
{
    QString OS;
    #ifdef Q_WS_X11
    OS = "Linux";
    #endif
    #ifdef Q_WS_WIN
    OS = "Win";
    #endif
    #ifdef Q_WS_MACX
    OS = "Mac";
    #endif
    return OS;
}

QStringList filestuff::listFiles(QString directory, QString filter, QString sort, bool reversed)
{
    QStringList results;
    bool empty;
    QDir dir = directory;
    if(filter == "files"){
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    }
    else if(filter == "folders"){
        dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    }
    if(reversed){
        dir.setSorting(QDir::Reversed);
    }
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i){
       QFileInfo fileInfo = list.at(i);
       results.append(fileInfo.fileName());
       empty = false;
    }
    if(empty == true){
        results.append("Nothing Here!");
    }
    return results;
}

bool filestuff::exMake(QString path)
{
    QDir dir(path);
    if (dir.exists()){
        return true;
    } else if (!dir.exists()) {
        dir.mkpath(path);
        return false;
    }
    return true;
}

void filestuff::removeDir(QString dirName)
{
    QDir dir(dirName);
    QStringList dirList(dir.entryList(QDir::Files));
    for (int i = 0; i < dirList.count(); i++){
        QString fName(dirName + "/" + dirList[i]);
        QFile::remove(fName);
    }
    dirList.clear();
    dirList = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    for (int i = 0; i < dirList.count(); i++){
        QString fName(dirName + "/" + dirList[i]);
        removeDir(fName);
    }
    dir.rmdir(dirName);
}

void filestuff::copyDir(QString src, QString dest)
{
    exMake(dest);
    QDir srcDir(src);
    QDir destDir(dest);
    QStringList srcList(srcDir.entryList(QDir::Files));
    for (int i = 0; i < srcList.count(); i++){
        QString srcName(src + "/" + srcList[i]);
        QString destName(dest + "/" + srcList[i]);
        QFile::copy(srcName, destName);
    }
    srcList.clear();
    srcList = srcDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    for (int i = 0; i < srcList.count(); i++){
        QString srcName(src + "/" + srcList[i]);
        QString destName(dest + "/" + srcList[i]);
        copyDir(srcName, destName);
    }
}

QString filestuff::mcDir()
{
    QString result = st.read("general", "mcdir", "none").toString();
    if (result == "none")
    {
        QString os = getOS();
        if (os == "Win"){
            result = QDir::homePath() + "/appdata/roaming/.minecraft";
        } else if (os == "Mac") {
            result = QDir::homePath() + "/Library/Application Support/minecraft";
        } else if (os == "Linux") {
            result = QDir::homePath() + "/.minecraft";
        }
    }
    st.write("general", "mcdir", result);
    return result;
}

QString filestuff::appDir()
{
    QString result = st.read("general", "appdir", "none").toString();
    if (result == "none")
    {
        QString os = getOS();
        if (os == "Win"){
            result = QDir::homePath() + "/appdata/roaming/MCMx";
        } else if (os == "Mac") {
            result = QDir::homePath() + "/Library/Application Support/MCMx";
        } else if (os == "Linux") {
            result = QDir::homePath() + "/.MCMx";
        }
    }
    exMake(result);
    exMake(result + "/backups");
    st.write("general", "appdir", result);
    return result;
}
