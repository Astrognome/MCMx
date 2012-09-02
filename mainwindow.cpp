#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "worldbackup.h"
#include "settings.h"

#include <QDir>

worldbackup wb;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("Application Started Successfully");
    loadSettings();
    refreshWorlds(true);
    refreshBackups();
}

MainWindow::~MainWindow()
{
    delete ui;
    saveSettings();
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
    ui->wb_stack->setCurrentIndex(1);
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
