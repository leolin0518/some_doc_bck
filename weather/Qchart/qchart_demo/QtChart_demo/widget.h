#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

/*QtChart的地方需要包含#include <QtCharts>以及命名空间using namespace QtCharts;
 * （或者QT_CHARTS_USE_NAMESPACE替代using namespace QtCharts;）
 * 但是ui_widget文件是自动生成的，不能再此文件里进行修改，此文件是包含在widget.h的一个叫Ui的命名空间中
 * 所以把
 * #include <QtCharts>
 * QT_CHARTS_USE_NAMESPACE
 * 放在.h文件里面
*/
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void splineChart_demo();//简单的线条曲线图 http://doc.qt.io/qt-5/qtcharts-splinechart-example.html
    void splineChart_sinx_demo();//正弦sin函数图 http://blog.csdn.net/czyt1988/article/details/51399341

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
