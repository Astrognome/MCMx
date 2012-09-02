#include "general.h"

#include <QString>
#include <QStringList>
#include <QMessageBox>

general::general()
{

}

int general::showMessage(QString message, QString infMessage, QString type)
{
    int retInt;
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.setInformativeText(infMessage);
    if (type == "yn"){ //yes-no box (0 = no, 1 = yes)
        msgBox.setStandardButtons(
                    QMessageBox::Yes |
                    QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int result = msgBox.exec();
        switch(result){
            case QMessageBox::No:
                retInt = 0;
                break;
            case QMessageBox::Yes:
                retInt = 1;
                break;
            default:
                retInt = -1;
                break;
        }
    } else if (type == "y"){ //okay box
        msgBox.setStandardButtons(
                    QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Yes);
        msgBox.exec();
        retInt = 1;
    }
    return retInt;
}
