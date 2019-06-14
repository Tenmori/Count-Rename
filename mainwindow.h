#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stdheader.h"
#include "corefunctions.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    coreFunctions *core;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pathEdit_textEdited(const QString &arg1);

    void on_nameEdit_textEdited(const QString &arg1);

    void on_countStart_valueChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    std::string path;
    std::string newNameFormat;
    int countStart;
    pathvec fileList;
};

#endif // MAINWINDOW_H
