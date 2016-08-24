#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QDebug>
#include <QString>
#include <iostream>
#include <QTextStream>
#include <QFileDialog>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();

private slots:
    void on_pushButton_path_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_checkprint_clicked();

    void on_pushButton_load_clicked();

    void on_comboBox_sheet_currentTextChanged(const QString &arg1);

    void on_comboBox_hang_value_currentTextChanged(const QString &arg1);


private:
    Ui::MainWindow *ui;


public slots:   //接收按钮信号的槽函数
  //  void load_hang_value();//

public:


private:
    QString excel_path_file;
    QString print_demo;
};

#endif // MAINWINDOW_H
