#include <QtGui/QApplication>
#include "mainwindow.h"

#include <iostream>
#include <string>
#include <cmath>
#include "godunov.h"
#include <QTest>
#include <cstdlib>
#include <cstdio>
#include "test_smart.h"

using namespace std;




int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

