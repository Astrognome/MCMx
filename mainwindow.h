#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_quitButton_clicked();

    void on_refreshListsButton_clicked();

    void on_worldList_currentRowChanged();

    void on_wb_advancedButton_clicked();

    void on_pushButton_5_clicked();

    void on_wb_makeBackupDataButton_clicked();

    void on_wb_createBackupButton_clicked();

    void on_wb_deleteBackupButton_clicked();

    void on_wb_restoreBackup_clicked();

    void on_wb_compApply_clicked();

    void on_launchSite1_clicked();

    void on_launchSite2_clicked();

    void on_dowloadLauncher_clicked();

public slots:

    void showStatus(QString text);

private:
    Ui::MainWindow *ui;

    void saveSettings();
    void loadSettings();
    void refreshWorlds(bool startup);
    void refreshBackups();

signals:
};

#endif // MAINWINDOW_H
