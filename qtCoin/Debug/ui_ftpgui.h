/********************************************************************************
** Form generated from reading UI file 'ftpgui.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FTPGUI_H
#define UI_FTPGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FTPGUI
{
public:
    QGridLayout *gridLayout;
    QLineEdit *statusBar;
    QToolButton *toolButtonBrowse;
    QPushButton *pushButtonExit;
    QLineEdit *lineEditPort;
    QCheckBox *checkBoxOnlyOneIpAllowed;
    QLineEdit *lineEditRootPath;
    QCheckBox *chkboxuserslist;
    QLineEdit *lineEditPassword;
    QLineEdit *lineEditUserName;
    QLabel *label_4;
    QPushButton *pushButtonRestartServer;
    QCheckBox *checkBoxAnonymous;
    QLabel *label_5;
    QLabel *label_3;
    QPushButton *pushButtonShowDebugLog;
    QCheckBox *checkBoxReadOnly;
    QListWidget *usersList;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QLineEdit *insertUser;
    QPushButton *adduserbtn;
    QPushButton *rmuserbtn;
    QPushButton *savesettings;

    void setupUi(QDialog *FTPGUI)
    {
        if (FTPGUI->objectName().isEmpty())
            FTPGUI->setObjectName(QString::fromUtf8("FTPGUI"));
        FTPGUI->resize(580, 470);
        gridLayout = new QGridLayout(FTPGUI);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        statusBar = new QLineEdit(FTPGUI);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));

        gridLayout->addWidget(statusBar, 8, 2, 1, 1);

        toolButtonBrowse = new QToolButton(FTPGUI);
        toolButtonBrowse->setObjectName(QString::fromUtf8("toolButtonBrowse"));

        gridLayout->addWidget(toolButtonBrowse, 3, 4, 1, 1);

        pushButtonExit = new QPushButton(FTPGUI);
        pushButtonExit->setObjectName(QString::fromUtf8("pushButtonExit"));

        gridLayout->addWidget(pushButtonExit, 8, 3, 1, 2);

        lineEditPort = new QLineEdit(FTPGUI);
        lineEditPort->setObjectName(QString::fromUtf8("lineEditPort"));

        gridLayout->addWidget(lineEditPort, 0, 1, 1, 3);

        checkBoxOnlyOneIpAllowed = new QCheckBox(FTPGUI);
        checkBoxOnlyOneIpAllowed->setObjectName(QString::fromUtf8("checkBoxOnlyOneIpAllowed"));

        gridLayout->addWidget(checkBoxOnlyOneIpAllowed, 5, 2, 1, 1);

        lineEditRootPath = new QLineEdit(FTPGUI);
        lineEditRootPath->setObjectName(QString::fromUtf8("lineEditRootPath"));
        lineEditRootPath->setReadOnly(true);

        gridLayout->addWidget(lineEditRootPath, 3, 1, 1, 3);

        chkboxuserslist = new QCheckBox(FTPGUI);
        chkboxuserslist->setObjectName(QString::fromUtf8("chkboxuserslist"));

        gridLayout->addWidget(chkboxuserslist, 4, 2, 1, 1);

        lineEditPassword = new QLineEdit(FTPGUI);
        lineEditPassword->setObjectName(QString::fromUtf8("lineEditPassword"));

        gridLayout->addWidget(lineEditPassword, 2, 1, 1, 3);

        lineEditUserName = new QLineEdit(FTPGUI);
        lineEditUserName->setObjectName(QString::fromUtf8("lineEditUserName"));

        gridLayout->addWidget(lineEditUserName, 1, 1, 1, 3);

        label_4 = new QLabel(FTPGUI);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 8, 0, 1, 1);

        pushButtonRestartServer = new QPushButton(FTPGUI);
        pushButtonRestartServer->setObjectName(QString::fromUtf8("pushButtonRestartServer"));

        gridLayout->addWidget(pushButtonRestartServer, 4, 3, 1, 2);

        checkBoxAnonymous = new QCheckBox(FTPGUI);
        checkBoxAnonymous->setObjectName(QString::fromUtf8("checkBoxAnonymous"));

        gridLayout->addWidget(checkBoxAnonymous, 4, 0, 1, 2);

        label_5 = new QLabel(FTPGUI);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        label_3 = new QLabel(FTPGUI);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        pushButtonShowDebugLog = new QPushButton(FTPGUI);
        pushButtonShowDebugLog->setObjectName(QString::fromUtf8("pushButtonShowDebugLog"));

        gridLayout->addWidget(pushButtonShowDebugLog, 5, 3, 1, 2);

        checkBoxReadOnly = new QCheckBox(FTPGUI);
        checkBoxReadOnly->setObjectName(QString::fromUtf8("checkBoxReadOnly"));

        gridLayout->addWidget(checkBoxReadOnly, 5, 0, 1, 1);

        usersList = new QListWidget(FTPGUI);
        usersList->setObjectName(QString::fromUtf8("usersList"));

        gridLayout->addWidget(usersList, 10, 1, 1, 2);

        label = new QLabel(FTPGUI);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(FTPGUI);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        insertUser = new QLineEdit(FTPGUI);
        insertUser->setObjectName(QString::fromUtf8("insertUser"));

        verticalLayout->addWidget(insertUser);

        adduserbtn = new QPushButton(FTPGUI);
        adduserbtn->setObjectName(QString::fromUtf8("adduserbtn"));

        verticalLayout->addWidget(adduserbtn);

        rmuserbtn = new QPushButton(FTPGUI);
        rmuserbtn->setObjectName(QString::fromUtf8("rmuserbtn"));

        verticalLayout->addWidget(rmuserbtn);


        gridLayout->addLayout(verticalLayout, 10, 0, 1, 1);

        savesettings = new QPushButton(FTPGUI);
        savesettings->setObjectName(QString::fromUtf8("savesettings"));

        gridLayout->addWidget(savesettings, 10, 3, 1, 1);


        retranslateUi(FTPGUI);

        QMetaObject::connectSlotsByName(FTPGUI);
    } // setupUi

    void retranslateUi(QDialog *FTPGUI)
    {
        FTPGUI->setWindowTitle(QApplication::translate("FTPGUI", "Dialog", nullptr));
        toolButtonBrowse->setText(QApplication::translate("FTPGUI", "...", nullptr));
        pushButtonExit->setText(QApplication::translate("FTPGUI", "Exit", nullptr));
        lineEditPort->setText(QApplication::translate("FTPGUI", "21", nullptr));
        checkBoxOnlyOneIpAllowed->setText(QApplication::translate("FTPGUI", "Only one IP allowed", nullptr));
        lineEditRootPath->setText(QApplication::translate("FTPGUI", "./", nullptr));
        chkboxuserslist->setText(QApplication::translate("FTPGUI", "usersList", nullptr));
        lineEditPassword->setText(QApplication::translate("FTPGUI", "test", nullptr));
        lineEditUserName->setText(QApplication::translate("FTPGUI", "admin", nullptr));
        label_4->setText(QApplication::translate("FTPGUI", "Status:", nullptr));
        pushButtonRestartServer->setText(QApplication::translate("FTPGUI", "Start/Restart FTP Server", nullptr));
        checkBoxAnonymous->setText(QApplication::translate("FTPGUI", "Allow anonymous login", nullptr));
        label_5->setText(QApplication::translate("FTPGUI", "Root path:", nullptr));
        label_3->setText(QApplication::translate("FTPGUI", "Password:", nullptr));
        pushButtonShowDebugLog->setText(QApplication::translate("FTPGUI", "Debug Console", nullptr));
        checkBoxReadOnly->setText(QApplication::translate("FTPGUI", "Read-only", nullptr));
        label->setText(QApplication::translate("FTPGUI", "Port:", nullptr));
        label_2->setText(QApplication::translate("FTPGUI", "User:", nullptr));
        insertUser->setText(QApplication::translate("FTPGUI", "username:password", nullptr));
        adduserbtn->setText(QApplication::translate("FTPGUI", "Add", nullptr));
        rmuserbtn->setText(QApplication::translate("FTPGUI", "Remove", nullptr));
        savesettings->setText(QApplication::translate("FTPGUI", "SaveSettings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FTPGUI: public Ui_FTPGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FTPGUI_H
