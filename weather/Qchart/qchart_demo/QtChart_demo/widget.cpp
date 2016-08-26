#include "widget.h"
#include "ui_widget.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>

//QT_CHARTS_USE_NAMESPACE  //定义在widget.h

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    splineChart_demo();//简单的线条曲线图
    //splineChart_sinx_demo();//正弦sin函数图
}

Widget::~Widget()
{
    delete ui;
}

void Widget::splineChart_demo()
{
    QLineSeries *series  = new QLineSeries();
    series->setName(tr("dddd"));
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);//把曲线添加到chart上
    chart->setTitle("Simple spline chart example");
    chart->createDefaultAxes();//创建曲线的轴
    chart->axisY()->setRange(0, 10);//设置Y轴范围为0-10
    //chart->axisX()->setRange(0, 30);//设置X轴的范围，如果不设置，将默认取当前线段上的点的最大x,y的值作为最大range
    ui->chart->setRenderHint(QPainter::Antialiasing);//防止曲线出现“锯齿”现象
    //ui->chart->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    ui->chart->setChart(chart);


//    QChartView *chartView = new QChartView(chart);
//    chartView->setRenderHint(QPainter::Antialiasing);

//    QMainWindow window;
//    window.setCentralWidget(chartView);
//    window.resize(400, 300);
//    window.show();


}

void Widget::splineChart_sinx_demo()
{
    QLineSeries* line1 = new QLineSeries();
    for(double x=0;x<10;x+=0.1)
    {
        line1->append(x,sin(x));
    }
    QChart* c = new QChart();
    c->addSeries(line1);
    ui->chart->setChart(c);
}
