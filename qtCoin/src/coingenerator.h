#ifndef COINGENERATOR_H
#define COINGENERATOR_H
#include <mainwindow.h>
#include "ui_mainwindow.h"
#include <math.h>
//#include <QCoreApplication>
#include <QFile>
#include <QDebug>
//#include <QMainWindow>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QTextCodec>

QString MainWindow::getClientAddress()
{ //change to getclientaddress instead
    int length = 8;
    QString clientaddress = m_strYear + GetRandomString(length, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890");
    return clientaddress;
}

void MainWindow::selectUsersCoins(QString userid, QString yeardb) // not ready yet
{
    m_DB.setDatabaseName("./db/" + yeardb + ".sqlite");
    if (m_DB.open())
    {
        qDebug() << "Successful database connection";
    }
    else
    {
        qDebug() << "Error: failed database connection";
    }

    QString query;
    query.append("SELECT * FROM " + userid);

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

void MainWindow::generateRCoins()
{
    //read coins.txt and send them to new availablecoins database
    QFile MyFile("coins.txt");
    MyFile.open(QIODevice::ReadOnly);
    QTextStream in(&MyFile);
    MyFile.seek(0);
    QString line;
    QStringList list;
    QStringList nums;

    QVariantList coins;
    QVariantList index;
    qDebug() << "filling coins list";
    while (in.readLineInto(&line))
    {
        QRegExp rx("[:]"); // match a comma or a space
        list = line.split(rx);
        index << list.at(0).toLatin1();
        coins << list.at(1).toLatin1();
    }

    createFreeCoinTable("rcoins.sqlite");
    qDebug() << "generating availablecoins";
    //sqlite create randomized availablecoins
    m_DB.setDatabaseName("rcoins.sqlite");
    if (m_DB.open())
    {
        qDebug() << "Successful coin database connection";
    }
    else
    {
        qDebug() << "Error: failed database connection";
    }

    m_DB.transaction();

    QString query2 = "INSERT INTO coins(origid,addr) VALUES (?,?)";

    //    qDebug() << query;
    QSqlQuery insert;
    insert.prepare(query2);
    insert.addBindValue(index);
    insert.addBindValue(coins);

    if (insert.execBatch())
    {
        qDebug() << "Coin is properly inserted";
    }
    else
    {
        qDebug() << "ERROR! " << insert.lastError();
    }
    m_DB.commit();
    index.clear();
    coins.clear();
    insert.clear();
    m_DB.close();

    //generate md5sum
    QByteArray coinstxtmd5 = fileChecksum("rcoins.sqlite", QCryptographicHash::Md5);

    QTextCodec *codec = QTextCodec::codecForName("KOI8-R");
    // codec->toUnicode(coindb)

    //QFile hashfile("hashes.txt");
    //if(hashfile.open(QIODevice::WriteOnly | QIODevice::Text))
    //{
    //    QTextStream stream(&hashfile);
    //    //hashfile.seek(0);
    //    stream << "coinstxt:" << coinstxtmd5.toHex() << endl;
    //    stream << "coinsdb:" << coindb.toHex() << endl;
    //    stream << "availableCoins:" << availablecoins.toHex() << endl;
    //}
    //hashfile.close();
}

void MainWindow::createCoinTable(QString DBname)
{
    m_DB.setDatabaseName(DBname.toLatin1());
    if (m_DB.open())
    {
        qDebug() << "Successful coin database connection";
    }
    else
    {
        qDebug() << "Error: failed database connection";
    }

    QString query;
    query.append("CREATE TABLE IF NOT EXISTS coins("
                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                 "addr VARCHAR(50));");

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

void MainWindow::createFreeCoinTable(QString DBname)
{
    m_DB.setDatabaseName(DBname.toLatin1());

    if (m_DB.open())
    {
        qDebug() << "Successful coin database connection";
    }
    else
    {
        qDebug() << "Error: failed database connection";
    }

    QString query;
    query.append("CREATE TABLE IF NOT EXISTS coins("
                 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                 "origid VARCHAR(50),"
                 "addr VARCHAR(50));");

    //    query.prepare("INSERT INTO employee (id INTEGER PRIMARY KEY AUTOINCREMENT, origid , addr) "
    //                  "VALUES (:id, :origid, :coin)");
    //    query.prepare("INSERT INTO employee (id, origid, addr) "
    //                  "VALUES (?, ?, ?)");

    //    query.addBindValue(1001);
    //    query.addBindValue("Thad Beaumont");
    //    query.addBindValue(65000);

    //    query.bindValue(":id", 1001);
    //    query.bindValue(":origid", "Thad Beaumont");
    //    query.bindValue(":addr", 65000);

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

void MainWindow::RandomizeCoins()
{
    //read coins.db into memory to try and open both sqldb at same time or write to textfile then read back in
    m_DB.setDatabaseName("coins.sqlite");
    QStringList tables = m_DB.tables();
    if (m_DB.open())
    {
        qDebug() << "Successful coin database connection";
    }
    else
    {
        qDebug() << "Error: failed database connection";
    }

    qDebug() << "randomizing";

    QSqlQuery query;

    query.prepare("SELECT * FROM coins ORDER BY random()");

    QFile file("coins.txt");
    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(&file);
        if (!query.exec())
        {
            qCritical() << query.lastQuery();
            qCritical() << query.lastError().databaseText();
            qCritical() << query.lastError().driverText();
            return;
        }

        query.next();
        while (query.isValid())
        {
            stream << query.value("id").toString() << ":" << query.value("addr").toString() << "\n";
            query.next();
        }
    }
    file.close();
    query.clear();
    m_DB.close();

    createCoinTable("availableCoins.sqlite");
    //read coins.txt and send them to new availablecoins database
    QFile MyFile("coins.txt");
    MyFile.open(QIODevice::ReadOnly);
    QTextStream in(&MyFile);
    MyFile.seek(0);
    QString line;
    QStringList list;
    QStringList nums;

    QVariantList coins;
    QVariantList index;
    qDebug() << "filling coins";
    while (in.readLineInto(&line))
    {
        QRegExp rx("[:]"); // match a comma or a space
        list = line.split(rx);
        coins << list.at(1).toLatin1();
    }
    qDebug() << "generating available coins";
    //sqlite create randomized availablecoins
    m_DB.setDatabaseName("availableCoins.sqlite");
    if (m_DB.open())
    {
        qDebug() << "Successful coin database connection";
    }
    else
    {
        qDebug() << "Error: failed database connection";
    }

    m_DB.transaction();

    QString query2 = "INSERT INTO coins(addr) VALUES (?)";

    // qDebug() << query;
    QSqlQuery insert;
    insert.prepare(query2);
    insert.addBindValue(coins);

    if (insert.execBatch())
    {
        qDebug() << "Coin is properly inserted";
    }
    else
    {
        qDebug() << "ERROR! " << insert.lastError();
    }
    m_DB.commit();
    coins.clear();
    insert.clear();
    m_DB.close();

    writeAdminFrontendHashes();
}

void MainWindow::insertCoins()
{
    //https://stackoverflow.com/questions/1711631/improve-insert-per-second-performance-of-sqlite
    //https://forum.qt.io/topic/86846/insert-data-into-sqlite-is-very-slow-by-qsqlquery/5
    //https://stackoverflow.com/questions/31197144/why-is-my-sqlite-query-so-slow-in-qt5/31208237
    m_DB.setDatabaseName("coins.sqlite");
    if (m_DB.open())
    {
        qDebug() << "Successful coin database connection";
    }
    else
    {
        qDebug() << "Error: failed database connection";
    }

    m_DB.transaction();
    QString query = "INSERT INTO coins(addr) VALUES (?)";
    QVariantList coins;
    for (int k = 0; k < m_Coins.count(); k++)
    {
        coins << m_Coins[k];

        //        query += "INSERT INTO coins(addr) VALUES ('" + _coins[k] + "');";
    }
    // coins << QVariant(QVariant::String);

    //    qDebug() << query;
    QSqlQuery insert;
    insert.prepare(query);
    insert.addBindValue(coins);

    if (insert.execBatch())
    {
        qDebug() << "Coin is properly inserted";
    }
    else
    {
        qDebug() << "ERROR! " << insert.lastError();
    }
    m_DB.commit();
    m_Coins.clear();
    insert.clear();
    m_DB.close();
}

int MainWindow::md5verifydb()
{
    // md5sum coinsdb maybe choose semirandom coinsammount to make md5 more unique
    // save with settings.txt
    //verify databases

    //encrypt hashes for extra security store them on thumbdrive too also keep plaintext unencrypted versions on local

    QFile MyFile("hashes.txt");
    MyFile.open(QIODevice::ReadWrite);
    QTextStream in(&MyFile);
    QString line;
    QStringList list;
    QStringList nums;

    do
    {
        line = in.readLine();
        QString searchString = ":";
        if (line.contains(searchString))
        { //, Qt::CaseSensitive
            // do something
            QRegExp rx("[:]"); // match a comma or a space
            list = line.split(rx);
            nums.append(list.at(1).toLatin1());
        }
    } while (!line.isNull());

    QString coinstxtmd5 = nums.at(0);
    ui->coinname->setText(coinstxtmd5.toLatin1());
    qDebug("%s", qUtf8Printable(coinstxtmd5));

    QString coindb = nums.at(1);
    ui->coinname->setText(coindb.toLatin1());
    qDebug("%s", qUtf8Printable(coindb));

    QString availablecoins = nums.at(2);
    ui->coinname->setText(availablecoins.toLatin1());
    qDebug("%s", qUtf8Printable(availablecoins));

    QByteArray coinstxtmd52 = fileChecksum("coins.txt", QCryptographicHash::Md5);
    QByteArray coindb2 = fileChecksum("coins.sqlite", QCryptographicHash::Md5);
    QByteArray availablecoins2 = fileChecksum("availableCoins.sqlite", QCryptographicHash::Md5);

    //QTextCodec *codec = QTextCodec::codecForName("KOI8-R");

    if (coinstxtmd5.toLatin1() == coinstxtmd52.toHex() && coindb.toLatin1() == coindb2.toHex() && availablecoins.toLatin1() == availablecoins2.toHex())
    {
        //           QMessageBox Msgbox;
        //               Msgbox.setText("verified ");
        //               Msgbox.exec();
        return 1;
    }

    return 0;
    //md5 convert coinsdb to randomcoins.db then md5sum can also check freecoins.db after each tx
}

void MainWindow::on_btn_GenerateCoin_clicked()
{
    if ((ui->coincount->text().toInt() & 1) != 0)
    {
        QMessageBox Msgbox;
        Msgbox.setText("needs to be even number: ");
        Msgbox.exec();
        return;
    }

    // check if odd or even
    QFile Fout("coins.sqlite");
    if (Fout.exists())
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Already Exists", "do you want to generate new coindb",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            qDebug() << "Yes was clicked";
            ClearTablesUsers();
        }
        else
        {
            qDebug() << "no";
            return;
        }
    }
    Fout.close();

    createCoinTable("coins.sqlite");
    m_nCoinIndex = 0;
    m_bGenerateToText = 0; // use 0 for sql
    GenerateCoins3(ui->coinlength->text().toInt(), ui->coincount->text().toInt());
    RandomizeCoins();
    generateRCoins();
    QString tester1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
    masterkey = GetRandomString(12, tester1.toLatin1());
    QThread::usleep(8000);
    m_strCoinKey = GetRandomString(12, tester1.toLatin1());

    QMessageBox Msgbox;
    Msgbox.setText("coin created: ");
    Msgbox.exec();
    on_btn_GenCoinInfo_clicked(); // save info
}

void MainWindow::generateCoins() //puts coins in text file to be read in by randomizer
{
    //  qDebug() << "generating coins to textfile";

    QFile file("coins2.txt");
    if (file.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) // QIODevice::Append |
    {
        QTextStream stream(&file);
        file.seek(0);
        for (int i = 0; i < m_Coins.count(); i++)
        {
            stream << QString::number(m_nCoinIndex) << ":" << m_Coins[i] << endl;
            m_nCoinIndex++;
        }
    }
    m_Coins.clear();
    file.close();
}

void MainWindow::GenerateCoins3(int length, int total)
{
    QString arrm = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
    QString arr = GetRandomString(15, arrm.toLatin1());
    m_strCoinKey = arr;

    QString data;
    m_nTotal = total;
    m_nCount = 0;
    m_nState = false;
    m_nLength = length;

    for (int i = 0; i < m_nLength; i++)
    {
        data += " ";
    }

    qDebug() << "running combo util";
    combinationUtil(arr, arr.length(), m_nLength, 0, data, 0);
}

void MainWindow::combinationUtil(QString arr, int n, int r, int index, QString data, int i)
{
    if (m_nState)
        return;
    if (index == r)
    {
        m_Coins.append(data);
        if (m_bGenerateToText == 1)
        {
            if (m_Coins.count() >= m_nTotal / 10) // misses if there arnt more than 80 coins so need to generatelastbit
            {
                //textversion
                generateCoins();
            }
        }
        else
        {
            if (m_Coins.count() >= m_nTotal / 10)
            {
                //sqlversion
                insertCoins();
            }
        }
        m_nCount++;
        if (m_nCount >= m_nTotal)
        {
            m_nState = true;
        }
        return;
    }

    if (i >= n)
        return;

    data[index] = arr[i];
    combinationUtil(arr, n, r, index + 1, data, i + 1);
    combinationUtil(arr, n, r, index, data, i + 1);
}

#endif // COINGENERATOR_H
