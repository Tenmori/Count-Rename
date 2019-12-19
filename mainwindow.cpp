#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    core(new class core()),
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

void MainWindow::on_pathEdit_2_textEdited(const QString &arg1)
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


void MainWindow::on_goRename_Button_clicked()
{
    MainWindow::fileList = core->read_directory(MainWindow::path);

    pathvec placeholder;

    MainWindow::finishedFileList = MainWindow::fileList;

    placeholder = core->rename_directory_files(MainWindow::actionType, MainWindow::fileList, MainWindow::newNameFormat, MainWindow::path, MainWindow::countStart);

    MainWindow::fileList = placeholder;

    core->document_changes(finishedFileList, fileList);

    ui->pathEdit->setText("");
    ui->nameEdit->setText("");
}

void MainWindow::on_undo_Button_clicked()
{
    std::cout << finishedFileList.size() << std::endl;

    std::cout << fileList.size() << std::endl;

    for (size_t i = 0; i < fileList.size(); i++)
    {
        std::cout << finishedFileList.at(i) << " to " << fileList.at(i) << std::endl;
    }

    core->undo(MainWindow::finishedFileList, MainWindow::fileList);
}

void MainWindow::on_searchPath_clicked()
{
    QString newPath = QFileDialog::getExistingDirectory(this, "Get Any File");
    ui->pathEdit->setText(newPath);
}

void MainWindow::on_searchPath_2_clicked()
{
    QString newPath = QFileDialog::getExistingDirectory(this, "Get Any File");
    ui->pathEdit_2->setText(newPath);
}

void MainWindow::on_phrase_textEdited(const QString &arg1)
{
    MainWindow::phrase = arg1.toStdString();
}

void MainWindow::on_goRemove_Button_clicked()
{
    MainWindow::fileList = core->read_directory(MainWindow::path);

    MainWindow::finishedFileList = MainWindow::fileList;

    if (MainWindow::phrase.size()>1)
    {
        MainWindow::fileList = core->cleanUp(MainWindow::fileList, MainWindow::path, true, MainWindow::phrase);
    }else
    {
        MainWindow::fileList = core->cleanUp(MainWindow::fileList, MainWindow::path, false, "NULL");
    }

    core->document_changes(finishedFileList, fileList);

    ui->pathEdit_2->setText("");
    ui->phrase->setText("");

}
void MainWindow::on_undo_Button_2_clicked()
{
    core->undo(MainWindow::finishedFileList, MainWindow::fileList);
}
