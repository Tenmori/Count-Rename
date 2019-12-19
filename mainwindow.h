#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stdheader.h"
#include "core.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    core *core;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pathEdit_textEdited(const QString &arg1);

    void on_nameEdit_textEdited(const QString &arg1);

    void on_countStart_valueChanged(int arg1);

    void on_goRename_Button_clicked();

    void on_undo_Button_clicked();

    void on_actionTypeSelector_currentIndexChanged(int index);

    void on_searchPath_clicked();

    void on_goRemove_Button_clicked();

    void on_pathEdit_2_textEdited(const QString &arg1);

    void on_searchPath_2_clicked();

    void on_phrase_textEdited(const QString &arg1);

    void on_undo_Button_2_clicked();

private:
    Ui::MainWindow *ui;
    std::string path;
    std::string newNameFormat;
    std::string phrase;
    int countStart;
    int actionType = 0;
    pathvec fileList;
    pathvec finishedFileList;
};

#endif // MAINWINDOW_H
