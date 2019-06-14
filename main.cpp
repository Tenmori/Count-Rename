#include "mainwindow.h"
#include <QApplication>

/*
 * Programmer: Tian K.
 * Date of Creation: 13/06/2019
 *
 * Renames all files of a given folder.
 *
 * Main
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
