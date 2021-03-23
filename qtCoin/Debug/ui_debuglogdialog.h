/********************************************************************************
** Form generated from reading UI file 'debuglogdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBUGLOGDIALOG_H
#define UI_DEBUGLOGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DebugLogDialog
{
public:
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit;
    QPushButton *btn_Close;

    void setupUi(QDialog *DebugLogDialog)
    {
        if (DebugLogDialog->objectName().isEmpty())
            DebugLogDialog->setObjectName(QString::fromUtf8("DebugLogDialog"));
        DebugLogDialog->resize(692, 344);
        verticalLayout = new QVBoxLayout(DebugLogDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        plainTextEdit = new QPlainTextEdit(DebugLogDialog);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        verticalLayout->addWidget(plainTextEdit);

        btn_Close = new QPushButton(DebugLogDialog);
        btn_Close->setObjectName(QString::fromUtf8("btn_Close"));

        verticalLayout->addWidget(btn_Close);


        retranslateUi(DebugLogDialog);

        QMetaObject::connectSlotsByName(DebugLogDialog);
    } // setupUi

    void retranslateUi(QDialog *DebugLogDialog)
    {
        DebugLogDialog->setWindowTitle(QApplication::translate("DebugLogDialog", "Dialog", nullptr));
        btn_Close->setText(QApplication::translate("DebugLogDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DebugLogDialog: public Ui_DebugLogDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUGLOGDIALOG_H
