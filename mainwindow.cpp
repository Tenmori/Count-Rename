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
}

void MainWindow::on_nameEdit_textEdited(const QString &arg1)
{
    MainWindow:: newNameFormat = arg1.toStdString();
}

void MainWindow::on_countStart_valueChanged(int arg1)
{
    MainWindow::countStart = arg1;
}

void MainWindow::on_actionTypeSelector_currentIndexChanged(int index)
{
    actionType = index;
}


void MainWindow::on_go_Button_clicked()
{
    MainWindow::fileList = core->read_directory(MainWindow::path);
    core->rename_directory_files(MainWindow::actionType, MainWindow::fileList, MainWindow::newNameFormat, MainWindow::path, MainWindow::countStart);
    MainWindow::finishedFileList = MainWindow::fileList;
    MainWindow::fileList = core->read_directory(MainWindow::path);
    core->document_changes(finishedFileList, fileList);
}

void MainWindow::on_undo_Button_clicked()
{
    core->rename_directory_files(2, MainWindow::finishedFileList, MainWindow::newNameFormat, MainWindow::path, MainWindow::countStart);
}
