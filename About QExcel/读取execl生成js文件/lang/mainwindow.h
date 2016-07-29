#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAxObject>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void on_StartButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_clicked();

   // void create_js_flies(QString path_dir);//创建js

private:
    Ui::MainWindow *ui;

    //for execl start
    QAxObject *pApplication;
    QAxObject *pWorkBooks;
    QAxObject *pWorkBook;
    QAxObject *pSheets;
    QAxObject *pSheet;
    //end
};


#endif // MAINWINDOW_H
