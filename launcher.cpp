#include "launcher.h"
#include "networkops.h"
#include "mainwindow.h"
#include "bridge.h"
#include "filestuff.h"

#include <QByteArray>
#include <QFile>

launcher::launcher(QObject *parent)
{
}

QString launcher::launcherPath(){
    QString path(filestuff::appDir());
    path.append("/launcher.jar");
}

void launcher::downloadLauncher()
{
    networkops netOps;
    emit pushStatus("Downloading Launcher...");
    netOps.downloadFile(QUrl("http://i.ytimg.com/vi/gvdf5n-zI14/0.jpg"),
                        "/nope.jpg");
    //netOps.downloadFile(QUrl("https://s3.amazonaws.com/MinecraftDownload/launcher/minecraft.jar"),
                        //launcherPath());
}
