/*#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}*/


#include <QApplication>
#include <QDebug>
#include <QTextCodec>

#include "qexcel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec* codec = QTextCodec::codecForName("system");
    //QTextCodec::setCodecForCStrings(codec);
    //QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);

    //打开文件，取得工作簿
//    QExcel j("F:/pro/QtExcel/c.xlsx");
    QExcel j;
    //j.createNewExcel("F:/pro/QtExcel/cc.xlsx");
     j.createNewExcel("D:/push/QtExcel/lang11.xlsx");

    j.insertSheet("表5");
    j.selectSheet("表5");
    j.setCellString(1, 1, "addString");

    j.insertSheet("表4");
//    j.selectSheet("表4");

    j.insertSheet("表3");
//    j.selectSheet("表3");

    j.insertSheet("表2");
//    j.selectSheet("表2");

    j.insertSheet("表1");
    j.selectSheet("表1");

    //添加完表后在删除，不能直接删除Excel里面的全部表
    j.selectSheet("Sheet1");
    j.deleteSheet("Sheet1");
    j.selectSheet("Sheet2");
    j.deleteSheet("Sheet2");
    j.selectSheet("Sheet3");
    j.deleteSheet("Sheet3");

//    j.save();
    j.saveAs();
    j.close();

    //取得工作表数量
    //qDebug()<<"SheetCount"<<j.getSheetsCount();
    //激活一张工作表
    //j.selectSheet(1);
    //j.selectSheet("JSheet2");
    //取得工作表名称
    //j.selectSheet(1);
    //j.getSheetName();
    //qDebug()<<"SheetName 1"<<j.getSheetName(1);
    //取得工作表已使用范围
    //int topLeftRow, topLeftColumn, bottomRightRow, bottomRightColumn;
    //j.getUsedRange(&topLeftRow, &topLeftColumn, &bottomRightRow, &bottomRightColumn);
    //读值
    //j.getCellValue(2, 2).toString();
    //删除工作表
    //j.selectSheet("Sheet1");
    //j.selectSheet(1);
    //j.deleteSheet();
    //j.save();
    //插入数据



//    j.selectSheet("Sheet2");
//    j.setCellString(1, 7, "addString");
//    j.setCellString("A3", "abc");
//    j.save();
/*
    //合并单元格
    //j.selectSheet(2);
    //j.mergeCells("G1:H2");
    //j.mergeCells(4, 7, 5 ,8);
    //j.save();
    //设置列宽
    //j.selectSheet(1);
    //j.setColumnWidth(1, 20);
    //j.save();
    //设置粗体
    //j.selectSheet(1);
    //j.setCellFontBold(2, 2, true);
    //j.setCellFontBold("A2", true);
    //j.save();
    //设置文字大小
    //j.selectSheet(1);
    //j.setCellFontSize("B3", 20);
    //j.setCellFontSize(1, 2, 20);
    //j.save();
    //设置单元格文字居中
    //j.selectSheet(2);
    //j.setCellTextCenter(1, 2);
    //j.setCellTextCenter("A2");
    //j.save();
    //设置单元格文字自动折行
    //j.selectSheet(1);
    //j.setCellTextWrap(2,2,true);
    //j.setCellTextWrap("A2", true);
    //j.save();
    //设置一行自适应行高
    //j.selectSheet(1);
    //j.setAutoFitRow(2);
    //j.save();
    //新建工作表
    //j.insertSheet("abc");
    //j.save();
    //清除单元格内容
    //j.selectSheet(4);
    //j.clearCell(1,1);
    //j.clearCell("A2");
    //j.save();
    //合并一列中相同连续的单元格
    //j.selectSheet(1);
    //j.mergeSerialSameCellsInColumn(1, 2);
    //j.save();
    //获取一张工作表已用行数
    //j.selectSheet(1);
    qDebug()<<j.getUsedRowsCount();
    //设置行高
        //j.selectSheet(1);
        //j.setRowHeight(2, 30);
        //j.save();


    int topLeftRow, topLeftColumn, bottomRightRow, bottomRightColumn;

    j.getUsedRange(&topLeftRow,&topLeftColumn,&bottomRightRow,&bottomRightColumn);

    qDebug()<<topLeftRow<<topLeftColumn<<bottomRightRow<<bottomRightColumn;

//    for (int row = topLeftRow;row<bottomRightRow;row++)
//    {
//        for(int column=topLeftColumn;column<bottomRightColumn;column++)
//        {
//            qDebug()<<j.getCellValue(row,column);
//        }
//    }

    qDebug()<< j.getCellValue(10,1);
    qDebug()<< j.getCellValue(11,1);
    qDebug()<< j.getCellValue(12,1);
    qDebug()<< j.getCellValue(10,2);
    qDebug()<< j.getCellValue(11,2);
    qDebug()<< j.getCellValue(12,2);


    j.close();

    */

    qDebug()<<"App End";
    return a.exec();
}

