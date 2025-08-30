#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define TEMPERATURE_STARTING_COORDINATE 50//高温平均值起始坐标
#define SPAN_INDEX 5                   //温度曲线间隔指数
#define ORIGIN_SIZE 3                       //温度曲线原点大小

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include <WeatherTool.h>
#include <QLabel>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QMessageBox>
#include <weatherdata.h>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual bool eventFilter(QObject* watched,QEvent* event);
protected:

    void contextMenuEvent(QContextMenuEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void getWeatherInfo(QNetworkAccessManager *manager);
    void parseJson(QByteArray& bytes);
    void setLabelContent();
    void paintSunRiseSet();
    void paintCurve();
    virtual void keyPressEvent(QKeyEvent *event);

private slots:
    void slot_exitApp();
    void replayFinished(QNetworkReply* reply);


    void on_refreshBt_clicked();

    void on_searchBt_clicked();


private:
    Ui::MainWindow *ui;
    QMenu *exitMenu;//右键退出菜单
    QAction *exitAct;//退出行为
    QPoint mPos;//窗口移到的点
    QList<QLabel *> forecast_week_list;         //星期
    QList<QLabel *> forecast_date_list;         //日期
    QList<QLabel *> forecast_aqi_list;          //天气指数
    QList<QLabel *> forecast_type_list;         //天气
    QList<QLabel *> forecast_typeIco_list;      //天气图标
    QList<QLabel *> forecast_high_list;         //高温
    QList<QLabel *> forecast_low_list;          //低温

    QString url;        //接口链接
    QString city;       //访问的城市
    QString cityTmp;    //临时存放城市变量，防止输入错误城市的时候，原来的城市名称还在。
    WeatherTool tool;   //天气工具对象
    QNetworkAccessManager *manager;

    //本地数据
    Today today;
    Forecast forecast[6];


    const static QPoint sun[2];       //日出日落底线
    const static QRect sunRizeSet[2]; //日出日落时间
    const static QRect rect[2];       //日出日落圆弧


    QTimer *sunTimer;


};



#endif // MAINWINDOW_H
