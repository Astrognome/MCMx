#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "worldbackup.h"
#include "settings.h"
#include "launcher.h"

#include <QDir>

worldbackup wb;
launcher launch;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("Application Started Successfully");
    loadSettings();
    refreshWorlds(true);
    refreshBackups();

    connect(&launch, SIGNAL(pushStatus(QString)),
            this, SLOT(showStatus(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    saveSettings();
}

void MainWindow::showStatus(QString text)
{
    ui->statusBar->showMessage(text);
}

void MainWindow::saveSettings()
{
    settings st;
    st.write("window", "size", size());
    st.write("window", "pos", pos());
}

void MainWindow::loadSettings()
{
    settings st;
    resize(st.read("window", "size", QSize(800, 600)).toSize());
    move(st.read("window", "pos", QPoint(20, 20)).toPoint());
    //ui->tabWidget->setCurrentIndex(st.read("window", "tab", 0).toInt());
}

void MainWindow::on_quitButton_clicked()
{
    saveSettings();
    exit(1);
}

void MainWindow::refreshBackups()
{
    if (ui->worldList->currentRow() != -1)
    {
        ui->backupList->clear();
        QString curWorld = ui->worldList->currentItem()->text();
        QStringList list(wb.listBackups(curWorld));
        ui->backupList->addItems(list);
    }
}

void MainWindow::refreshWorlds(bool startup)
{
    settings st;
    if(startup == false){
        st.write("wb","worldlistpos",ui->worldList->currentRow());
    }
    ui->worldList->clear();
    QStringList list(wb.listWorlds());
    ui->worldList->addItems(list);
    ui->worldList->setCurrentRow(st.read("wb","worldlistpos",0).toInt());
}

void MainWindow::on_refreshListsButton_clicked()
{
    refreshWorlds(false);
    refreshBackups();
    ui->statusBar->showMessage("Refreshed Successfully");
}

void MainWindow::on_worldList_currentRowChanged()
{
    settings st;
    refreshBackups();
    st.write("wb","worldlistpos",ui->worldList->currentRow());
}

void MainWindow::on_wb_advancedButton_clicked() //change wb to page 2
{
    QString world(ui->worldList->currentItem()->text());
    ui->wb_stack->setCurrentIndex(1);
    if (wb.worldConf_Read(world, "compression/enabled", false).toBool()){
        ui->wb_compCompCmdLE->setText(
                    wb.worldConf_Read(world, "compression/compresscmd", "").toString());
        ui->wb_compDecompCmdLE->setText(
                    wb.worldConf_Read(world, "compression/restorecmd", "").toString());
        ui->wb_compStack->setCurrentIndex(1);
        ui->wb_storageMethodBox->setCurrentIndex(1);
    } else {
        ui->wb_compCompCmdLE->clear();
        ui->wb_compDecompCmdLE->clear();
        ui->wb_compStack->setCurrentIndex(0);
        ui->wb_storageMethodBox->setCurrentIndex(0);
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->wb_stack->setCurrentIndex(0);
}

void MainWindow::on_wb_makeBackupDataButton_clicked()
{
    wb.createBackupData(ui->worldList->currentItem()->text());
}

void MainWindow::on_wb_createBackupButton_clicked()
{
    wb.createBackup(ui->worldList->currentItem()->text());
    ui->statusBar->showMessage("Backup Made");
    refreshBackups();
}

void MainWindow::on_wb_deleteBackupButton_clicked()
{
    wb.removeBackup(ui->worldList->currentItem()->text(),
                ui->backupList->currentItem()->text());
    refreshBackups();
    ui->statusBar->showMessage("Backup Removed");
}

void MainWindow::on_wb_restoreBackup_clicked()
{
    wb.restoreBackup(
                ui->worldList->currentItem()->text(),
                ui->backupList->currentItem()->text());
}

void MainWindow::on_wb_compApply_clicked()
{
    if(ui->wb_storageMethodBox->currentIndex() == 0){
        wb.compApply(ui->worldList->currentItem()->text(),
                     "","",false);
    } else if (ui->wb_storageMethodBox->currentIndex() == 1){
        wb.compApply(ui->worldList->currentItem()->text(),
                     ui->wb_compCompCmdLE->text(),
                     ui->wb_compDecompCmdLE->text(),true);
    }
}

void MainWindow::on_launchSite1_clicked() //minecraft.net
{
    ui->launchWebView->setUrl(QUrl("http://www.minecraft.net/"));
}

void MainWindow::on_launchSite2_clicked() //minecraftwiki.net
{
    ui->launchWebView->setUrl(QUrl("http://minecraftwiki.net/"));
}

void MainWindow::on_dowloadLauncher_clicked()
{
    launch.downloadLauncher();
    ui->statusBar->showMessage("Launcher Dowloaded");
}
