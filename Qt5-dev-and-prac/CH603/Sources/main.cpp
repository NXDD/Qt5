#include "mainwindow.h"
#include <QApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);       //新建字体
    QFont font("ZYSong18030", 12);    //整个窗口应用该字体
    a.setFont(font);
    MainWindow w;
    w.show();

    return a.exec();
}
