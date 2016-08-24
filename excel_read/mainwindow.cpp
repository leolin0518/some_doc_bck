#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXlsx>
#include <QTextStream>
#include <QDir>
#include "xlsxabstractsheet.h"
#include <QMessageBox>

QTXLSX_USE_NAMESPACE        //该命名空间不可少
int sheet_row;//表 最大行数
int sheet_col;//表 最大列数

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();

    //connect(ui->comboBox_sheet, SIGNAL(currentIndexChanged(int)), this, SLOT(load_hang_value()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
      MainWindow::setWindowTitle(tr("Excel读取 v0.1"));
      ui->tabWidget->setCurrentWidget(ui->tab_1);

}

//excel path click路径
void MainWindow::on_pushButton_path_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,tr("Select Excel File"),
                                                   "C:/Users/Administrator/Desktop",tr("Excel(*xlsx *xls)"));
    QString tmp = fileNames.join(",");
    QString tmp_path = tmp.section(',',0,0);//多个文件时，分割，截取第一个
    qDebug()<< "tmp:" << tmp ;
    qDebug()<< "tmp_path:" << tmp_path;
    excel_path_file = tmp_path;
    qDebug()<< "path_file:" << excel_path_file;
    if(excel_path_file.endsWith("xls") == true)
    {
        //QMessageBox::about(NULL, "warning", "只能处理xlsx的文件，请将xls文件另存为xlsx格式文件");
        QMessageBox::information(NULL,"warning","只能处理xlsx格式的文件，\n请将xls文件另存为xlsx格式文件",QMessageBox::Ok);
        return ;
    }
    ui->label_excel_path->setText(excel_path_file);

}



//开始生成
void MainWindow::on_pushButton_start_clicked()
{
    ui->textBrowser_print->clear();

     qDebug()<< "22222222";
    // QXlsx::Document xlsx;
     QXlsx::Document xlsx(excel_path_file);

     qDebug()<< "..........ui->comboBox_sheet->currentText()..................:" << ui->comboBox_sheet->currentText();
    xlsx.selectSheet(ui->comboBox_sheet->currentText());
   // xlsx_tmp.selectSheet(arg1);
    QStringList sheetname = xlsx.sheetNames();
    QString www = xlsx.read("C1").toString();
    qDebug()<< "xx:" << www ;
    qDebug()<< "sheetname:" << sheetname ;




    //获取当前文件路径
    QString path;
    QDir dir;
    path=dir.currentPath(); //path为QString类型
    qDebug()<< path;
    QString path_dir = path+"/生成文件/" + ui->comboBox_sheet->currentText();
    if(!dir.exists(path_dir))
    {
      //dir.mkdir(path_dir); //上层目录不存在时，创建会失败。比如创建“c:\\test\test”
                            //如果test不存在，那test也创建不了。目录已经存在时会返回false。
      dir.mkpath(path_dir);//上层目录不存，自动一起创建。目录已经存在时会返回true。
      qDebug()<<"mkdir dir:" <<path_dir;
    }

    //创建xx.txt文件
    QString sheet_name =  path_dir + "/" + ui->comboBox_sheet->currentText() + ".txt"; //表名 例：menu.txt
    qDebug()<<"sheet_name:"<<sheet_name;
    QFile file(sheet_name);
    if(!file.open((QIODevice::WriteOnly)))
    {
        file.close();
        return;
    }

    //打开txt文件
    if(!file.open(QIODevice::WriteOnly))
    {
        //qDebug()<<"Can't open the file!"<<endl;
    }
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    QString line_in;
    if(ui->textEdit_1->toPlainText().isEmpty() == false) //段首 不为空
    {
        QString textEdit_1 = ui->textEdit_1->toPlainText();
        stream<< textEdit_1 << endl;
    }



    QString hang_shou = ui->textEdit_2->toPlainText();
   // qDebug() << "hang_shou:" << hang_shou;

    QString hang_wei = ui->textEdit_3->toPlainText();
   // qDebug() << "hang_wei:" << hang_wei;
    int lie_no = ui->comboBox_hang_value->currentIndex() + 1;
   // qDebug() << "lie_no:" << lie_no;

    ui->textBrowser_print->append("正在生成......" );
    qDebug() << "sheet_row..................:" << sheet_row  << "  ...........:"<< sheet_col;
    for (int row=2; row <= sheet_row; ++row)//hang
    {
        if (QXlsx::Cell *cell=xlsx.cellAt(row, lie_no))
        {
            qDebug()<<cell->value();
            QString cell_vlue =  cell->value().toString();
            line_in =  hang_shou + cell_vlue + hang_wei ;
        }
       // qDebug() << "line_in:" << line_in;
        stream<< line_in << endl;


        // int load = row/800;
         //QString s = QString("%1").arg(load);
        // QString load_str = "已完成：" + s + "%";
        // ui->textBrowser_log->append(load_str);

    }


    if(ui->textEdit_4->toPlainText().isEmpty() == false) //段尾 不为空
    {
        QString textEdit_4 = ui->textEdit_4->toPlainText();
        stream<< textEdit_4 << endl;
    }

    ui->textBrowser_print->append("生成 ...ok" );
    ui->textBrowser_print->append("\n\n生成的文件在软件的同目录下！" );



}


//显示打印预览
void MainWindow::on_pushButton_checkprint_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_2);
    QString duan_shou = ui->textEdit_1->toPlainText();
    qDebug() << "duan_shou:" << duan_shou;

    QString hang_shou = ui->textEdit_2->toPlainText();
    qDebug() << "hang_shou:" << hang_shou;

    QString hang_wei = ui->textEdit_3->toPlainText();
    qDebug() << "hang_wei:" << hang_wei;

    QString duan_wei = ui->textEdit_4->toPlainText();
    qDebug() << "duan_wei:" << duan_wei;

    QString print_line1 =  hang_shou + "excel_cell_value(DEMO)" + hang_wei ;
    QString print_line2 =  hang_shou + "excel_cell_value(DEMO)" + hang_wei ;
    QString print_demo = duan_shou + '\n' +
                            "        " + print_line1 + '\n' +
                            "        " + print_line2 + '\n' +
                         duan_wei;
    qDebug() << "print_demo:" << print_demo;

    ui->textBrowser_print->setText(print_demo);
}


//加载。获取exeel里的表单，并设置
void MainWindow::on_pushButton_load_clicked()
{
    QXlsx::Document xlsx_tmp(excel_path_file);//E:/Git/Qt/excel_read/Profile TR098.xlsx
    QStringList sheetname_tmp = xlsx_tmp.sheetNames();//表单名
    qDebug() << "表单名:"  << sheetname_tmp;
    ui->comboBox_sheet->addItems(sheetname_tmp);
    QString tmp = sheetname_tmp.join(",");
    qDebug() << "tmp:"  << tmp;
    //ui->textBrowser_print->append("当前文件中的sheet:"+ tmp);
    ui->labelsheet_log->setText("当前文件中表单为:"+ tmp);


   //获取选择表单的行列
   //xlsx_tmp.selectSheet(arg1);//选中表单
   QXlsx::CellRange range;
   range = xlsx_tmp.dimension();
   sheet_row = range.rowCount();//行
   sheet_col = range.columnCount();//列
   qDebug() << "打印当前表的行sheet_row:" << sheet_row << "   打印当前表的列sheet_col:" << sheet_col;

}


//设置当前选中的表里面是项（列）
void MainWindow::on_comboBox_sheet_currentTextChanged(const QString &arg1)
{
    qDebug()<< "设置当前选中的表里面是项（列）:" << arg1;
    //ui->labelsheet_log->setText(arg1);
    QXlsx::Document xlsx_tmp(excel_path_file);
   // QXlsx::Document xlsx_tmp("C:/Users/Administrator/Desktop/excel/Profile TR098.xlsx");
    xlsx_tmp.selectSheet(arg1);
    QStringList hang_vlue;

    for (int column=1; column<= 5; ++column)
    {
        if (QXlsx::Cell *cell=xlsx_tmp.cellAt(1, column))
        {
            qDebug()<<cell->value();
            hang_vlue << cell->value().toString();
        }
    }
    qDebug()<< "hang_vlue:" << hang_vlue;
    ui->comboBox_hang_value->clear();
    ui->comboBox_hang_value->addItems(hang_vlue);
}

//选中表的项
void MainWindow::on_comboBox_hang_value_currentTextChanged(const QString &arg1)
{
    //ui->textBrowser_log->append("选中的列为:"+ arg1);
    //ui->textBrowser_print->append("选中的列为:"+ arg1);
    ui->labelsheet_log->setText("当前表单：" + ui->comboBox_sheet->currentText() + " 选中的列为:"+ arg1);
}
