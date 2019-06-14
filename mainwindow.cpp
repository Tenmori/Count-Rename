#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    core(new coreFunctions()),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pathEdit_textEdited(const QString &arg1)
{
    MainWindow::path = arg1.toStdString();

    MainWindow::fileList = core->read_directory(MainWindow::path);
}

void MainWindow::on_nameEdit_textEdited(const QString &arg1)
{
    MainWindow:: newNameFormat = arg1.toStdString();
}

void MainWindow::on_countStart_valueChanged(int arg1)
{
    MainWindow::countStart = arg1;
}

void MainWindow::on_pushButton_clicked()
{
    core->rename_directory_files(MainWindow::fileList, MainWindow::newNameFormat, MainWindow::path, MainWindow::countStart);
}
