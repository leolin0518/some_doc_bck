#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QString>
#include<iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QAxObject excel("Excel.Application");//连接Excel控件
    excel.setProperty("Visible",false);//不显示execl的窗体
    QAxObject *workbooks = excel.querySubObject("WorkBooks");//获取工作簿集合
    qDebug("workbooks:%p", workbooks);
    //cout<<"test"<<endl ;
    workbooks->dynamicCall("Open (const QString&)",QString("D:/lang11.xlsx"));//打开execl表

    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");//获取活动工作簿
    qDebug("workbooks:%s", workbook);
    QAxObject *worksheets = workbook->querySubObject("WorkSheets");//获取所有的工作表
    int sheet_number = worksheets->property("Count").toInt();
    qDebug("intCount:%d",sheet_number);


    for (int i = 1; i <= sheet_number; i++)
    {
        int intVal;
        QAxObject * worksheet = workbook->querySubObject("Worksheets(int)", i);
        qDebug() << i << worksheet->property("Name").toString();


        QAxObject * range = worksheet->querySubObject("Cells(1,1)");//获取execl表的第一个表格cell的值
        intVal = range->property("Value").toInt();
        cout<< intVal <<endl;
        range->setProperty("Value", QVariant(intVal+1));
        QAxObject * range2 = worksheet->querySubObject("Range(C1)");
        intVal = range2->property("Value").toInt();
        cout<< intVal <<endl;
        range2->setProperty("Value", QVariant(intVal+1));

    }

    /*
    QAxObject * worksheet = workbook->querySubObject("Worksheets(int)", 1);
    QAxObject * usedrange = worksheet->querySubObject("UsedRange");
    QAxObject * rows = usedrange->querySubObject("Rows");
    QAxObject * columns = usedrange->querySubObject("Columns");
    int intRowStart = usedrange->property("Row").toInt();
    int intColStart = usedrange->property("Column").toInt();
    int intCols = columns->property("Count").toInt();
    int intRows = rows->property("Count").toInt();
    for (int i = intRowStart; i < intRowStart + intRows; i++)
    {
        for (int j = intColStart; j <= intColStart + intCols; j++)
        {
            QAxObject * range = worksheet->querySubObject("Cells(int,int)", i, j );
            qDebug() << i << j << range->property("Value");
        }
    }
    */







    //QAxObject *worksheet = workbook->querySubObject("WorkSheets(int)",1);//获取工作表集合的工作表1，即sheet1



    //QAxObject *range = worksheet->querySubObject("Cells(int,int)",1,1); //获取cell的值
    //QString strVal = range->dynamicCall("Text").toString();//保存



    // ui->label->setText(strVal);



}

MainWindow::~MainWindow()
{
    delete ui;
    //for execl start
    pApplication = NULL;
    pWorkBooks = NULL;
    pWorkBook = NULL;
    pSheets = NULL;
    pSheet = NULL;
    //end
}
