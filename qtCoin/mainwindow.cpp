#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QClipboard>
#include <QStandardItemModel>
//#include <QtCore>
#include <src/coingenerator.h>
#include <src/coinfunctions.h>
#include <src/validatecoins.h>
#include "src/encryption/encryption.h"
#include "src/encryption/rsa/Rsa.h"
#include "src/downloadmanager.h"
#include "src/loadtheme.h"
#include "src/devices.h"
#include "src/admin.h"
#include "src/wallet.h"
#include "src/email.h"
#include "src/ftp-server/ftpgui.h"
#include <src/oglwidget.h>

/*
    references and links
https://doc.qt.io/qt-5/sql-sqlstatements.html
https://www.techonthenet.com/mysql/select.php
http://ismacs.net/singer_sewing_machine_company/why-two-serial-numbers.html some of the first serial numbers
https://patents.google.com/patent/US3988571A/en
*/

//encrypt with usbdrivename
#ifdef FTP
FTPGUI *ftpgui;
#endif

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    m_fVersion = 0.6;

    ui->setupUi(this);
    qDebug() << "Application initialized...";

    m_DB = QSqlDatabase::addDatabase("QSQLITE");
    m_DB.setDatabaseName("database.sqlite");
#ifdef SOUND
    player = new QMediaPlayer();
    playsound("Resource/sounds/ec1_mono.ogg");
#endif
    qDebug() << "db exists" << QDir("db").exists();
    if (!QDir("db").exists())
    {
        QDir().mkdir("db");
    }

    //set global current year
    QDate curDate = QDate::currentDate();
    m_strYear = QString::number(curDate.year());

    ui->createyear->setValue(curDate.year());
    ui->createmonth->setCurrentIndex(curDate.month() - 1);
    ui->createday->setValue(curDate.day());
    ui->matureyear->setValue(curDate.year()+1);

    ui->maturemonth->setCurrentIndex(curDate.month() - 1);
    ui->matureday->setValue(curDate.day());
    QTime starttime(QTime::currentTime().hour(), QTime::currentTime().minute()); //12:00AM
    ui->createtime->setTime(starttime);

    //load settings File/OpenCoinDB
    if (QFileInfo("settings.txt").exists())
    {
        on_actionOpenCoin_triggered();
    }
    // load email settings
    getEmailSettings();

    this->setWindowTitle(ui->coinname->text());
    // themeInit();

    //subtract date to set progress bar

    //convert to days then set progressbar
    ui->matureyear->text();
    ui->maturemonth->currentText();

    QDate dNow(QDate::currentDate());
    QDate createdate(ui->createyear->text().toInt(), ui->createmonth->currentIndex() + 1, ui->createday->text().toInt());
    QDate maturedate(ui->matureyear->text().toInt(), ui->maturemonth->currentIndex() + 1, ui->matureday->text().toInt());
    qDebug() << ui->matureyear->text().toInt() << ui->maturemonth->currentIndex() + 1 << ui->matureday->text().toInt();
    qDebug() << "leap year detector" << QDate::isLeapYear(m_strYear.toInt());
    qDebug() << "Today is" << dNow.toString("dd.MM.yyyy")
             << "maturedate is" << maturedate.toString("dd.MM.yyyy")
             << "days to maturing: "
             << dNow.daysTo(maturedate);

    float daysElapsed = createdate.daysTo(maturedate) - dNow.daysTo(maturedate); // days elapsed since creation
    float daysTotalMaturing = createdate.daysTo(maturedate);
    float test4 = daysElapsed / daysTotalMaturing * 100;
    ui->pg_Mature->setValue(test4);

    // might have to contact server for ammount available
    ui->pg_MatureAvalability->setValue(100);

#ifdef ENCRYPTION
    rsaTester = new Rsa();
    rsaTester->publish_keys(m_e, m_n);
#endif
    // m_bAdmin = true;
    if (getkeys() == 1)
    {
        m_bAdmin = true;
    }
    else
    {
        //testing
        QString tester1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
        masterkey = GetRandomString(12, tester1.toLatin1());
        m_strCoinKey = "testing1234567";
    }
    if (QFileInfo("wallet.sqlite").exists())
    {
        m_bWalletExists = true;
    }

    if (!m_bAdmin && m_bWalletExists)
    {
        //set to client mode
        m_nTabindex = 1;
        removedTab = ui->app->widget(m_nTabindex);
        AddRemoveTab(ui->admintab, "Admin", m_nTabindex);
    }
    else
    {
    }

#ifdef OPENGL
    // widget = new IrrlichtWidget( ui->tabWidget->findChild<QWidget *>("irrRenderWidget0") );
    // QOpenGLWidget
    // OGLWidget *widget2 = new OGLWidget(ui->tabWidget_2->findChild<QWidget *>("openGLWidget"));
    // widget2->(ui->openGLWidget->height());
    // OGLWidget *openGLWidget = new OGLWidget(parent);
    // openGLWidget->show();
    // ui->openGLWidget->resize(300,400);
    // widget2->resize(ui->openGLWidget->width(),ui->openGLWidget->height());
    // ui->openGLWidget->showMaximized();
    //  setCentralWidget(widget); //widget
    //  showMaximized();
    //  widget2->autoRepaint();
#endif
    m_hDbus = NULL;
    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.registerObject("/qtcoin", this);
    connection.registerService("qtcoin.test");
    connection.connect("my.qtcoin.dbus", "/qtcoin", "qtcoin.test", "test", this, SLOT(remoteCall(QString)));
}

MainWindow::~MainWindow()
{
    if(m_hDbus != NULL)
    {
        m_hDbus->stop();
        while (m_hDbus->isRunning());
        delete m_hDbus;
    }
    delete ui;
}

void MainWindow::playsound(QString test)
{
#ifdef SOUND
    try{
        QFile file(test.toLatin1());
        file.open(QIODevice::ReadOnly);
        QByteArray *arr = new QByteArray(file.readAll());
        file.close();
        QBuffer *buffer = new QBuffer(arr);
        buffer->open(QIODevice::ReadOnly);
        buffer->seek(0);
        player->setVolume(10);
        player->setMedia(QMediaContent(), buffer);
        player->play();
    }catch(exception e)
    {
        printf("playsound Err:%s", e.what());
    }

#endif
}

void MainWindow::remoteCall(QByteArray message)
{
    std::cout << "Message size: " << message.size() << std::endl;
}
void MainWindow::remoteCall(QString message)
{
    std::cout << "Message size: " << message.size() << " data: " << message.toUtf8().constData() << std::endl;
}

void MainWindow::AddRemoveTab(QWidget *tab, QString name, int tabindex)
{
    if (tab->isEnabled())
    {
        ui->app->removeTab(tabindex);
        tab->setEnabled(false);
    }
    else
    {
        tab->setEnabled(true);
        ui->app->insertTab(tabindex, removedTab, name.toLatin1());
    }
}

void MainWindow::on_actionSyncUSB_triggered()
{
    ListUSB();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_matureradio_yes_clicked()
{
    ui->matureradio_no->setChecked(0);
}

void MainWindow::on_encrypted_yes_clicked()
{
    ui->encrypted_yes->setChecked(1);
}

void MainWindow::on_matureradio_no_clicked()
{
    ui->matureradio_no->setChecked(1);
}

void MainWindow::on_encrypted_no_clicked()
{
    //check to see if anything is already using encryption
    ui->encrypted_no->setChecked(1);
}

void MainWindow::on_btnClear_clicked() //clearall databases
{
    ClearTablesUsers();
}

void MainWindow::on_btn_FTPTest_clicked()
{
    serverusbtxrx();
    clientusbtxrx();

    QString test = rot13("test");
    qDebug() << "encrypted rot13:" << test;
    qDebug() << "decrypted rot13:" << rot13(test.toLatin1());
}

void MainWindow::on_btn_SaveUserInfo_clicked()
{
    //Download("ftp://127.0.0.1/");
}

void MainWindow::on_btn_placeCoinsOpenFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open rx/tx"), "./", tr("rx/tx files (*.rx *.tx *.txt)"));
    qDebug() << fileName.toLatin1();

    //check extension to see if image to decode qrcode.
    //save qrdata to tmp file set filename and process

    processRXTXfile(fileName);
}

void MainWindow::on_btn_CreateWallet_clicked()
{
    //could create wallet from server generated tx file or send one with first transaction online account registration
    // qDebug() << getHDserial();
    createWalletTable("");
}

void MainWindow::on_btn_UserGenerateQr_clicked()
{
    QString qrstring = ui->adduserEmail->text().toLatin1() + "::" +
                       ui->addusername->text().toLatin1() + "::" +
                       ui->lineEditPhone->text().toLatin1() + "::" +
                       ui->createuserdatetime->text().toLatin1() + "::" +
                       ui->createextra->text().toLatin1() + "::" +
                       ui->createclass->text().toLatin1();

    GenerateQRCode(qrstring, ui->adduserQRview);
}

void MainWindow::on_btn_AddressSearch_clicked()
{
    // auto model = new QStandardItemModel();
    // ui->treeView->setModel(model);
    // model->appendRow(new QStandardItem ("test"));
    // model->appendRow(new QStandardItem ("test"));
    // model->appendRow(new QStandardItem ("test"));

    // QList<QStandardItem*> test;
    // QStandardItem *test34 =new QStandardItem ("test");
    // test.append(test34);
    // model->item(1)->appendRows(test);
    // ui->treeView->expandAll();
}

void MainWindow::on_btn_AdminMode_clicked()
{
    // if no multiple wallet support then warn user it will erase wallet and to back it up to safe location
    AddRemoveTab(ui->admintab, "Admin", m_nTabindex);
}

void MainWindow::on_btn_FtpServer_clicked()
{
#ifdef FTP
    if (adminftp == 0)
    {
        ftpgui = new FTPGUI;
        adminftp = 1;
    }
    if (adminftp)
    {
        ftpgui->show();
    }
#endif
}

void MainWindow::on_CheckAvailability_clicked()
{
    //download info file from server
    m_DownLoadManager.Download("ftp://admin:qt@127.0.0.1:8258/available");
}

void MainWindow::on_updateVerify_clicked()
{
    //download all databases for verification of coins offline - still succeptable to double spend but atleast its able to work without server.
    //possibly place usersigned coins they would like to spend that day into a pickup database for the server to hold for them temporary holding when doing offline tx's
    m_DownLoadManager.Upload("ftp://127.0.0.1", "admin", "qt", "8258", "./ftp.ini");
}
