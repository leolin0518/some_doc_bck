#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qexcel.h"
#include <QFile>
#include <QDebug>
#include <QString>
#include <iostream>
#include <QTextStream>
#include <QFileDialog>
using namespace std;


/*************************************************************
*************************************************************/
int lang_list_num;
int topLeftRow, topLeftColumn, bottomRightRow, bottomRightColumn;
//QString path_file="D:/lang11.xlsx";
QString path_file="";



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_StartButton_clicked()  //开始生成xx.js
{

    //获取UI中语言，表单的值
    int current_lang_num = 0;
    int current_sheet_num = 0;
    bool sheet_all = false;
    current_lang_num = ui->LangBoxSelect->currentIndex()+2;//下拉项从0开始计数，加2，使下拉选项值与execl表中的语言表格相对应
    current_sheet_num = ui->SheetBoxSelect->currentIndex()+1;//表单值,从1开始计数，1表示第一个表单
    QString current_lang_str = ui->LangBoxSelect->currentText();
    qDebug() << "current_lang_str000000:" << current_lang_str;
    //sheet_all = ui->checkBox->clicked();
    qDebug()<< "LangNu:" << current_lang_num << "SheetNu:" << current_sheet_num;
    sheet_all = ui->checkBox->isChecked();
    qDebug()<<"ui->checkBox:"<<sheet_all;
    if(sheet_all) //表单全选
    {
        QExcel lang(path_file);
        int sheet_number = lang.getSheetsCount();
         for(int i = 1; i <= sheet_number; i++)
         {
               lang.selectSheet(i);//选中表单
               lang.getUsedRange(&topLeftRow, &topLeftColumn, &bottomRightRow, &bottomRightColumn);
               qDebug() << "topLeftCell("<<topLeftRow<<","<<topLeftColumn <<")";
               qDebug() << "" << lang.getCellValue(topLeftRow, topLeftColumn).toString();
               qDebug() << "bottomRightCell("<<bottomRightRow<<","<<bottomRightColumn <<")";
               qDebug() << "" << lang.getCellValue(bottomRightRow, bottomRightColumn).toString();

            #if 1
                //获取当前文件路径
                QString path;
                QDir dir;
                path=dir.currentPath(); //path为QString类型
                qDebug()<< path;
                QString path_dir = path+"/Language/" + current_lang_str;
                if(!dir.exists(path_dir))
                {
                    //dir.mkdir(path_dir); //上层目录不存在时，创建会失败。比如创建“c:\\test\test”
                                          //如果test不存在，那test也创建不了。目录已经存在时会返回false。
                    dir.mkpath(path_dir);//上层目录不存，自动一起创建。目录已经存在时会返回true。
                    //qDebug()<<"mkdir dir:" <<path_dir;
                }

                //创建xx.js文件            
                QString sheet_name =  path_dir + "/" + lang.getSheetName(); //表名 例：menu.js
                qDebug()<<"sheet_name:"<<sheet_name;
                QFile file(sheet_name);
                if(!file.open((QIODevice::WriteOnly)))
                {
                    file.close();
                    return;
                }
                //打开js文件
                if(!file.open(QIODevice::WriteOnly))
                {
                    //qDebug()<<"Can't open the file!"<<endl;
                }
                QTextStream stream(&file);
                stream.setCodec("UTF-8");
                QString line_in;
                stream<< "LangM.push({" << endl;
                for(int i=2; i <= bottomRightRow; i++) //bottomRightRow表的行数，语言翻译从表的第二行开始
                {
                    line_in = "'" + lang.getCellValue(i,1).toString() + "'" + ":" +
                              "'" + lang.getCellValue(i,current_lang_num).toString()+ "'" + ",";
                    stream<< line_in << endl;
                }
                stream<< "\"\":null});" << endl;
                ui->textBrowser->append((QObject::trUtf8("表："))+lang.getSheetName() +" ...ok" );
            #endif

         }


    }else
    {

        //QExcel lang("D:/lang11.xlsx");
        QExcel lang(path_file);
        //取得工作表已使用范围
        lang.selectSheet(current_sheet_num);//选中表单
        lang.getUsedRange(&topLeftRow, &topLeftColumn, &bottomRightRow, &bottomRightColumn);
        qDebug() << "topLeftCell("<<topLeftRow<<","<<topLeftColumn <<")";
        qDebug() << "" << lang.getCellValue(topLeftRow, topLeftColumn).toString();
        qDebug() << "bottomRightCell("<<bottomRightRow<<","<<bottomRightColumn <<")";
        qDebug() << "" << lang.getCellValue(bottomRightRow, bottomRightColumn).toString();

    #if 1
        //获取当前文件路径
        QString path;
        QDir dir;
        path=dir.currentPath(); //path为QString类型
        qDebug()<< path;
        QString path_dir = path+"/Language/" + current_lang_str;
        if(!dir.exists(path_dir))
        {
            //dir.mkdir(path_dir); //上层目录不存在时，创建会失败。比如创建“c:\\test\test”
                                  //如果test不存在，那test也创建不了。目录已经存在时会返回false。
            dir.mkpath(path_dir);//上层目录不存，自动一起创建。目录已经存在时会返回true。
            //qDebug()<<"mkdir dir:" <<path_dir;
        }

        //创建xx.js文件
        QString sheet_name =  path_dir + "/" + lang.getSheetName(); //表名 例：menu.js
        qDebug()<<"sheet_name:"<<sheet_name;
        QFile file(sheet_name);
        if(!file.open((QIODevice::WriteOnly)))
        {
            file.close();
            return;
        }
        //打开js文件
        if(!file.open(QIODevice::WriteOnly))
        {
            //qDebug()<<"Can't open the file!"<<endl;
        }
        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        QString line_in;
        stream<< "LangM.push({" << endl;
        for(int i=2; i <= bottomRightRow; i++) //bottomRightRow表的行数，语言翻译从表的第二行开始
        {
            line_in = "'" + lang.getCellValue(i,1).toString() + "'" + ":" +
                      "'" + lang.getCellValue(i,current_lang_num).toString()+ "'" + ",";
            stream<< line_in << endl;
        }
        stream<< "\"\":null});" << endl;
        ui->textBrowser->append((QObject::trUtf8("表："))+lang.getSheetName() +" ...ok" );
    #endif

    }

}

void MainWindow::on_pushButton_clicked()//选择xls表路径
{

    QStringList fileNames = QFileDialog::getOpenFileNames(this,tr("Select Excel File"),
                                                   "C:/Users/Administrator/Desktop",tr("Excel(*xlsx *xls)"));
    QString tmp = fileNames.join(",");
    QString tmp_path = tmp.section(',',0,0);//多个文件时，分割，截取第一个
    qDebug()<< "tmp:" << tmp ;
    qDebug()<< "tmp_path:" << tmp_path;
    path_file = tmp_path;
    qDebug()<< "path_file:" << path_file;
    ui->label_path->setText(path_file);
}

void MainWindow::on_pushButton_2_clicked()//加载
{
    //在语言下拉框添加execl中的语言列表，语言列表从execl中获取
    //QExcel lang("D:/lang11.xlsx");
    if(1) //加载前默认刷新下拉列表
    {
        ui->LangBoxSelect->clear();
        ui->SheetBoxSelect->clear();
    }

    if(!path_file.isEmpty())
    {
        QExcel lang(path_file);
        QString lang_list;
        lang.selectSheet(1);
        lang.getUsedRange(&topLeftRow, &topLeftColumn, &bottomRightRow, &bottomRightColumn);
        ui->textBrowser->append((QObject::trUtf8("当前有")) + QString::number(bottomRightColumn-1) + (QObject::trUtf8("种语言项")));
        for(int i =2; i <= bottomRightColumn; i++) //bottomRightColumn 表的列数
        {
            lang_list =  lang.getCellValue(1,i).toString();
            qDebug() << lang_list ;
            ui->LangBoxSelect->addItem(lang_list);
            ui->textBrowser->append((QObject::trUtf8("当前xls中语言有：")) + ((lang_list)));
        }

        //在表单下拉框添加execl中的表单的列表，表单列表从execl中获取
        int sheet_number = lang.getSheetsCount();
        qDebug()<<"SheetCount"<<lang.getSheetsCount();
        for(int i = 1; i <= sheet_number; i++)  //sheet_number execl中的表的数量
        {
            lang.selectSheet(i);//激活一张工作表
            QString sheet_name = lang.getSheetName();//取得工作表名称
            ui->SheetBoxSelect->addItem(sheet_name);
            qDebug() << "SheetName" << i << " :" << sheet_name;
        }

    }else{
        ui->LangBoxSelect->addItem("NULL");
        ui->SheetBoxSelect->addItem("NULL");

    }
}



void MainWindow::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked())
    {
        ui->textBrowser->append((QObject::trUtf8("------表单全选------")));
        ui->SheetBoxSelect->setEnabled(false);
    }else
    {
        ui->textBrowser->append((QObject::trUtf8("------全选取消------")));
        ui->SheetBoxSelect->setEnabled(true);
    }

}

/*
void MainWindow::create_js_flies(QString path_dir)
{
    QString file_path;
    QDir dir;
    file_path=dir.currentPath(); //path为QString类型
    qDebug()<< file_path;
    QString current_lang_name = ui->LangBoxSelect->currentText();//当前选中的语言

    QString path_dir = file_path+"/Language/" + current_lang_name;//创建的语言的文件夹路径
    if(!dir.exists(path_dir))
    {
        //dir.mkdir(path_dir); //上层目录不存在时，创建会失败。比如创建“c:\\test\test”
                              //如果test不存在，那test也创建不了。目录已经存在时会返回false。
        dir.mkpath(path_dir);//上层目录不存，自动一起创建。目录已经存在时会返回true。
        //qDebug()<<"mkdir dir:" <<path_dir;
    }

    //创建xx.js文件
    QString sheet_name =  path_dir + "/" + lang.getSheetName(); //表名 例：menu.js
    qDebug()<<"sheet_name:"<<sheet_name;
    QFile file(sheet_name);
    if(!file.open((QIODevice::WriteOnly)))
    {
        file.close();
        return;
    }
    //打开js文件
    if(!file.open(QIODevice::WriteOnly))
    {
        //qDebug()<<"Can't open the file!"<<endl;
    }
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    QString line_in;
    stream<< "LangM.push({" << endl;
    for(int i=2; i <= bottomRightRow; i++) //bottomRightRow表的行数，语言翻译从表的第二行开始
    {
        line_in = "'" + lang.getCellValue(i,1).toString() + "'" + ":" +
                  "'" + lang.getCellValue(i,current_lang_num).toString()+ "'" + ",";
        stream<< line_in << endl;
    }
    stream<< "\"\":null});" << endl;
}
*/
