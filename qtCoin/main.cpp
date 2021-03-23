#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include "src/qstylesheetmanager.h"
#include <QThread>
#include <QDebug>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    // QStyleSheetManager::loadStyleSheet("Resource/themes/style4.qss");

    MainWindow w;
    if (0)
    {
        QPixmap m("./Resource/qtcoin.png");
        QSplashScreen splash(m);
        splash.show();
        splash.finish(&w);
    }
    w.show();
    return a.exec();
}
