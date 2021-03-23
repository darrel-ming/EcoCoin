#ifndef WALLET_H
#define WALLET_H

#include <mainwindow.h>
#include "ui_mainwindow.h"
//#include <QCoreApplication>
#include <QFile>
#include <QDebug>
//#include <QMainWindow>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QTextCodec>
#include <QFileDialog>
#include <QClipboard>
#include <QByteArray>
#include <src/encryption/encryption.h>
#include <QDirIterator>

#include "quazip/quazip.h"
#include "quazip/quazipfile.h"
#include "quazip/JlCompress.h"

int MainWindow::createPickupCoinTable(QString eownerID)
{

    m_DB.setDatabaseName("./db/pickup.sqlite");

    if (m_DB.open())
    {
        qDebug() << "Successful database connection";
    }
    else
    {
        qDebug() << "Error: failed database connection";
    }

    QString query;

    qDebug() << "test" << eownerID.toLatin1();

    query.append("CREATE TABLE IF NOT EXISTS "
                 "'" +
                 eownerID.toLatin1() + "'"
                                       "("
                                       "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                       "origindex VARCHAR(100)," //rcoins index then coins.sqlite is stored on usbdrive as part of key/verify
                                       "addr VARCHAR(100),"
                                       "datetime INTEGER,"
                                       "class INTEGER,"
                                       "hold INTEGER"
                                       ");");

    QSqlQuery create;
    create.prepare(query);

    if (create.exec())
    {
        qDebug() << "Table exists or has been created";
    }
    else
    {
        qDebug() << "Table not exists or has not been created";
        qDebug() << "ERROR! " << create.lastError();
    }
    query.clear();
    m_DB.close();
}

int MainWindow::pickupCoinsInsert(QString eownerID, QString Coin)
{
    //createPickupCoinTable();
}

void MainWindow::serverusbtxrx()
{
    //automatic function to do rxtx from usb for cold storage

    //verify tx file apply
    QStringList list;
    //export db's and overwrite if valid
    QDirIterator it("./db/", QStringList() << "*.sqlite", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        //  QFileInfo fileInfo(f.fileName());
        list << it.next().toLatin1();
    }

#ifdef QUAZIP
    if (JlCompress::compressFiles("saveFile.zip", list))
    {
        //        QMessageBox Msgbox;
        //            Msgbox.setText("zipped");
        //            Msgbox.exec();
    }
    else
    {
        QMessageBox Msgbox;
        Msgbox.setText("zip file not found ");
        Msgbox.exec();
    }
#endif
}

void MainWindow::clientusbtxrx()
{
    //import db's and overwrite if valid md5sums after copying yearly dbs and md5sums from server
    //applying rx file to compare?

    QStringList list;
    //export db's and overwrite if valid
    QDirIterator it("./db/", QStringList() << "*.sqlite", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        //  QFileInfo fileInfo(f.fileName());
        list << it.next().toLatin1();
    }

#ifdef QUAZIP
    if (JlCompress::compressFiles("saveFile.zip", list))
    {
        //        QMessageBox Msgbox;
        //            Msgbox.setText("zipped");
        //            Msgbox.exec();
    }
    else
    {
        QMessageBox Msgbox;
        Msgbox.setText("zip file not found ");
        Msgbox.exec();
    }

    unCompress("saveFile.zip", "./db/");
#endif
}

void MainWindow::on_btn_SelectAll_clicked()
{
    selectUsers();
}

void MainWindow::on_btn_GenCoinInfo_clicked()
{
    qDebug() << "generating settings.txt";
    QFile file("settings.txt");
    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << "CoinName:" << ui->coinname->text() << '\n';
        stream << "CoinCount:" << ui->coincount->text() << '\n';
        stream << "CoinLength:" << ui->coinlength->text() << '\n';
        stream << "CreateDay:" << ui->createday->text() << '\n';
        stream << "CreateMonth: " << ui->createmonth->currentText() << '\n';
        stream << "CreateYear:" << ui->createyear->text() << '\n';
        stream << "CreateTime:" << ui->createtime->time().hour() << "|" << ui->createtime->time().minute() << '\n';
        stream << "CoinValue:" << ui->coinvalue->text() << '\n';
        stream << "Matures:" << ui->matureradio_yes->text() << '\n';
        stream << "Coinpayout:" << ui->coinpayout->text() << '\n';
        stream << "Encrypted:" << ui->encrypted_yes->text() << '\n';
        stream << "MatureDate:" << ui->matureday->text() << '\n';
        stream << "MatureMonth:" << ui->maturemonth->currentText() << '\n';
        stream << "MatureYear:" << ui->matureyear->text() << '\n';
        stream << "MatureTime:" << ui->maturetime->time().hour() << "|" << ui->maturetime->time().minute() << '\n';
        stream << "Maturedescription:" << ui->maturedescription->toPlainText() << '\n';
        stream << "UsbDriveName:" << ui->usbdrivename->text() << '\n'; //place into keys instead
        file.close();
    }

    ListUSB();

    qDebug() << "usb path " << m_strUsbPath.toLatin1();
    QString path;
    qDebug() << "usb path set.";
    if (m_strUsbPath.toLatin1() != "")
    {
        path = m_strUsbPath.toLatin1() + "/keys.txt";
    }
    else
    {
        qDebug() << "local keys path set.";
        path = "./keys.txt";
    }
    QFile file2(path);
    if (file2.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&file2);
        stream << "masterkey:" << masterkey.toLatin1() << '\n';
        stream << "coinkey:" << m_strCoinKey.toLatin1() << '\n';
        stream << "coinsmd5:" << fileChecksum("coins.sqlite", QCryptographicHash::Md5).toHex() << '\n';
        stream << "checksum:" << md5Checksum("masterkey:" + masterkey.toLatin1() + "coinkey:" + m_strCoinKey.toLatin1() + "coinsmd5:" + fileChecksum("coins.sqlite", QCryptographicHash::Md5)).toHex() << '\n';
        //  stream << "usbdrivename:" << ui->usbdrivename->text();
        file2.close();
    }
}

void MainWindow::on_btn_InsertUser_clicked()
{
    //QString temp = GenerateClientAddress(8);
    QString temp = GetRandomString(8, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890");
    ui->lineEditName->setText(m_strYear.toLatin1() + temp.toLatin1());
    //ui->lineEditName->setText(temp.toLatin1()); //testing
    QString ownerid = ui->lineEditName->text().toLatin1();
    QString password = ui->lineEditPassword->text();

    //    QString s = QDate::currentDate().toString();
    //    QDate::currentDate().day();
    //    QDate::currentDate().month();
    //    QDate::currentDate().year();
    QTime starttime(QTime::currentTime().hour(), QTime::currentTime().minute());
    QDate dNow(QDate::currentDate());
    ui->createuserdatetime->setText(dNow.toString("dd.MM.yyyy") + "T" + starttime.toString());

    //fix later
    if (validateID(ownerid) == 0)
    {
        for (int i = 0; i < 100; i++)
        { //100 tries
            if (validateID(ownerid) == 1)
            {
            }
            else
            {
                break;
            }
            QString temp = GetRandomString(8, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890");
            ownerid = ui->lineEditName->text().toLatin1();
        }
    }

    qDebug() << ownerid.toLatin1();

    QString crypted2 = simplecrypt(ownerid.toLatin1(), masterkey.toLatin1(), QCryptographicHash::Sha512);
    // QString decrypted = simpledecrypt(crypted,"test2",QCryptographicHash::Sha512);
    qDebug() << crypted2;
    ui->lineEditName->setText(crypted2.toLatin1());

    createyearly(crypted2);

    //  createyearly(crypted2); //the /n causes issues
    //  qDebug() << "lineeditname " << ui->lineEditName->text();

    insertUser();

    //selectUsersCoins(temp.toLatin1(),year.toLatin1());

    ui->lineEditName->setText(ownerid.toLatin1());
    ui->lineEditName->setEnabled(1);

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->lineEditName->text());

    on_btn_UserGenerateQr_clicked();

    selectUsers(); //refresh user table
}

void MainWindow::searchyearly(QString ownerID)
{
    m_DB.setDatabaseName("database.sqlite");
    if (m_DB.open())
    {
        qDebug() << "Successful database connection";
    }
    else
    {
        qDebug() << "Error: failed database connection";
    }

    QString query;
    query.append("SELECT * FROM " + ownerID);

    QSqlQuery select;
    select.prepare(query);

    if (select.exec())
    {
        qDebug() << "The user is properly selected";
    }
    else
    {
        qDebug() << "The user is not selected correctly";
        qDebug() << "ERROR! " << select.lastError();
    }

    int row = 0;
    ui->tableWidgetUsers->setRowCount(0);

    while (select.next())
    {
        ui->tableWidgetUsers->insertRow(row);
        ui->tableWidgetUsers->setItem(row, 0, new QTableWidgetItem(select.value(1).toByteArray().constData()));
        ui->tableWidgetUsers->setItem(row, 1, new QTableWidgetItem(select.value(2).toByteArray().constData()));
        ui->tableWidgetUsers->setItem(row, 2, new QTableWidgetItem(select.value(3).toByteArray().constData()));
        ui->tableWidgetUsers->setItem(row, 3, new QTableWidgetItem(select.value(4).toByteArray().constData()));
        row++;
    }

    query.clear();
    m_DB.close();
}

void MainWindow::createyearly(QString eownerID)
{
    //holds users generated from each new year and their coins pulled from rcoins.sqlite

    m_DB.setDatabaseName("./db/" + m_strYear + ".sqlite");

    if (m_DB.open())
    {
        qDebug() << "Successful database connection";
    }
    else
    {
        qDebug() << "Error: failed database connection";
    }

    QString query;

    qDebug() << "test" << eownerID.toLatin1();

    query.append("CREATE TABLE IF NOT EXISTS "
                 "'" +
                 eownerID.toLatin1() + "'"
                                       "("
                                       "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                       "origindex VARCHAR(100)," //rcoins index then coins.sqlite is stored on usbdrive as part of key/verify
                                       "addr VARCHAR(100),"
                                       "datetime INTEGER,"
                                       "class INTEGER,"
                                       "hold INTEGER"
                                       ");");

    QSqlQuery create;
    create.prepare(query);

    if (create.exec())
    {
        qDebug() << "Table exists or has been created";
    }
    else
    {
        qDebug() << "Table not exists or has not been created";
        qDebug() << "ERROR! " << create.lastError();
    }
    query.clear();
    m_DB.close();
}

void MainWindow::writeAdminFrontendHashes() // for startup and shutdown could be password protected
{
    //generate md5sum
    QByteArray coinstxtmd5 = fileChecksum("coins.txt", QCryptographicHash::Md5);
    QByteArray coindb = fileChecksum("coins.sqlite", QCryptographicHash::Md5);
    QByteArray availablecoins = fileChecksum("availableCoins.sqlite", QCryptographicHash::Md5);

    QTextCodec *codec = QTextCodec::codecForName("KOI8-R");
    // codec->toUnicode(coindb)

    QFile hashfile("hashes.txt");
    if (hashfile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&hashfile);
        //hashfile.seek(0);
        stream << "coinstxt:" << coinstxtmd5.toHex() << endl;
        stream << "coinsdb:" << coindb.toHex() << endl;
        stream << "availableCoins:" << availablecoins.toHex() << endl;
    }
    hashfile.close();
}

void MainWindow::ClearTablesUsers()
{
    // removes databases/users to start fresh
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Are you sure ?", "remova all tables/users ?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QFile::remove("./db/" + m_strYear + ".sqlite");

        QFile::remove("coins.txt");
        QFile::remove("database.sqlite");
        QFile::remove("coins.sqlite");
        QFile::remove("availableCoins.sqlite");
        QFile::remove("rcoins.sqlite");
        QFile::remove("hashes.txt");
    }
}

void MainWindow::createUserTable()
{
    m_DB.setDatabaseName("database.sqlite");
    if (m_DB.open())
    {
        qDebug() << "Successful database connection";
    }
    else
    {
        qDebug() << "Error: failed database connection";
    }
    QString query;

    query.append("CREATE TABLE IF NOT EXISTS users("
                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                 "email VARCHAR(100),"
                 "userid VARCHAR(100),"
                 "name VARCHAR(100),"
                 "password VARCHAR(100),"
                 "phone INTEGER," //                    "phone INTEGER NOT NULL,"
                 "datetime INTEGER NOT NULL,"
                 "ekey VARCHAR(100),"
                 "total VARCHAR(100),"
                 "extra VARCHAR(100),"
                 "class INTEGER"
                 ");");

    QSqlQuery create;
    create.prepare(query);

    if (create.exec())
    {
        qDebug() << "Table exists or has been created";
    }
    else
    {
        qDebug() << "Table not exists or has not been created";
        qDebug() << "ERROR! " << create.lastError();
    }
    query.clear();
    m_DB.close();
}

void MainWindow::selectUsers(QString strQuery)
{
    m_DB.setDatabaseName("database.sqlite");
    if (m_DB.open())
    {
        qDebug() << "Successful database connection";
    }
    else
    {
        qDebug() << "Error: failed database connection";
    }

    QString query;
    if(strQuery.length() == 0)
    {
        query = "SELECT * FROM users";
    }else{
        query = strQuery;
    }

    QSqlQuery select;
    select.prepare(query);

    if (select.exec())
    {
        qDebug() << "The user is properly selected";
    }
    else
    {
        qDebug() << "The user is not selected correctly";
        qDebug() << "ERROR! " << select.lastError();
    }

    int row = 0;
    ui->tableWidgetUsers->setRowCount(0);

    while (select.next())
    {
        ui->tableWidgetUsers->insertRow(row);
        ui->tableWidgetUsers->setItem(row, 0, new QTableWidgetItem(select.value(1).toByteArray().constData()));
        ui->tableWidgetUsers->setItem(row, 1, new QTableWidgetItem(select.value(2).toByteArray().constData()));
        ui->tableWidgetUsers->setItem(row, 2, new QTableWidgetItem(select.value(3).toByteArray().constData()));
        ui->tableWidgetUsers->setItem(row, 3, new QTableWidgetItem(select.value(10).toByteArray().constData()));
        ui->tableWidgetUsers->setItem(row, 4, new QTableWidgetItem(select.value(6).toByteArray().constData()));
        row++;
    }

    query.clear();
    m_DB.close();
}

void MainWindow::on_btn_Search_clicked() //search button
{
    QString query = "SELECT * FROM users WHERE name ='" + ui->userid->text() + "'";
    selectUsers(query);
}

void MainWindow::SQLTest(QString dbname, QString Query)
{
    m_DB.setDatabaseName(dbname.toLatin1());
    if (m_DB.open())
    {
        qDebug() << "Successful database connection";
    }
    else
    {
        qDebug() << "Error: failed database connection";
    }

    QString query;
    query.append(Query.toLatin1());

    QSqlQuery select;
    select.prepare(query);

    if (select.exec())
    {
        qDebug() << "The user is properly selected";
    }
    else
    {
        qDebug() << "The user is not selected correctly";
        qDebug() << "ERROR! " << select.lastError();
    }

    int row = 0;
    ui->tableWidgetUsers->setRowCount(0);

    while (select.next())
    {
        ui->tableWidgetUsers->insertRow(row);
        ui->tableWidgetUsers->setItem(row, 0, new QTableWidgetItem(select.value(0).toByteArray().constData()));
        ui->tableWidgetUsers->setItem(row, 1, new QTableWidgetItem(""));
        ui->tableWidgetUsers->setItem(row, 2, new QTableWidgetItem(""));
        ui->tableWidgetUsers->setItem(row, 3, new QTableWidgetItem(""));
        row++;
    }

    query.clear();
    m_DB.close();
}

void MainWindow::on_addUserQR_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save image", QCoreApplication::applicationDirPath(), "BMP Files (*.bmp);;JPEG (*.JPEG);;PNG (*.png)");
    if (!fileName.isNull())
    {
        QPixmap pixMap = this->ui->btn_UserGenerateQr->grab();
        pixMap.save(fileName);
    }
}

void MainWindow::insertUser() //strictly a db to hold all userid's for verification
{
    createUserTable();

    m_DB.setDatabaseName("database.sqlite");
    if (m_DB.open())
    {
        qDebug() << "Successful database connection";
    }
    else
    {
        qDebug() << "Error: failed database connection";
    }

    //could also use md5sum at time of creation for public key + time
    QString crypted2 = simplecrypt(ui->lineEditName->text(), masterkey.toLatin1(), QCryptographicHash::Sha512);

    QString query;

    // QString euserid = ui->lineEditName->text();
#ifdef ENCRYPTION
    QByteArray bFname = EncryptMsg(ui->lineEditName->text(), "123456789", "your-IV-vector");
    QString mykey1 = BigInt2Str(m_e); //rsa keys
    QString mykey2 = BigInt2Str(m_n); //rsa keys
#endif
        //generate public key and encrypt userid

    query.append("INSERT INTO users("
                 "email,"
                 "userid,"
                 "name,"
                 "password,"
                 "phone," //
                 "datetime,"
                 "ekey,"
                 "total,"
                 "extra,"
                 "class)"
                 "VALUES("
                 "'" +
                 ui->adduserEmail->text().toLatin1() + "',"
                                                       "'" +
                 crypted2.toLatin1() + "',"
                                       "'" +
                 ui->addusername->text().toLatin1() + "',"
                                                      "'" +
                 ui->lineEditPassword->text().toLatin1() + "',"
                                                           "'" +
                 ui->lineEditPhone->text().toLatin1() + "',"
                                                        "'" +
                 ui->createuserdatetime->text() + "',"
                                                  "'" +
                 GetReallyRandomString(8, "").toLatin1() + "'," //ekey
                                                           "'"
                                                           "'," //ammount
                                                           "'" +
                 ui->createextra->text().toLatin1() + "',"
                                                      "'" +
                 ui->createclass->text() + "'"
                                           ");");

    //  qDebug()<< euserid.toLatin1();

    QSqlQuery insert;
    insert.prepare(query);

    if (insert.exec())
    {
        qDebug() << "The user is properly inserted";
    }
    else
    {
        qDebug() << "The user is not inserted correctly";
        qDebug() << "ERROR! " << insert.lastError();
    }

    query.clear();
    m_DB.close();
}

#endif // WALLET_H
