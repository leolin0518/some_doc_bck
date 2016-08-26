#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QNetworkAccessManager;
class QNetworkRequest;
class QNetworkReply;

struct WeatherInfo{
    QString date;
    QString week;
    QString type;
    QString curTemp;
    QString hightemp;
    QString lowtemp;
    QString fengli;
    QString fengxiang;
    QString aqi;
};

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void init();
    void setTableHorizontalHeader();

    void getProvinceList();                     //获取省份列表
    void getCityList(QString arg);              //获取城市列表
    void getAreaList(QString arg);              //获取区域列表

    void setNetworkRequest(QNetworkRequest &request, QString cityName);//设置网络请求
    void getHistoryWeatherInfo(QJsonObject data);                   //获取历史天气信息
    void getTodayWeatherInfo(QJsonObject data);                     //获取当日天气信息
    void getForecastWeatherInfo(QJsonObject data);                  //获取未来天气信息
    void getOtherInfo(QJsonObject data);                            //获取其他天气信息
    void setAqi(QString &strAqi);                                   //设置空气质量指数显示

private slots:
    void replyFinished(QNetworkReply *reply);

    void on_btn_refresh_clicked();

    void on_cBox_province_activated(const QString &arg1);

    void on_cBox_city_activated(const QString &arg1);

private:
    Ui::Widget *ui;

    QStringList provinceList;               //省份列表
    QStringList cityList;                   //城市列表
    QStringList areaList;                   //区域列表

    QNetworkAccessManager *manage;
};

#endif // WIDGET_H
