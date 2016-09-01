#include "widget.h"
#include "dialog.h"
#include "weather.h"
#include "mainwindow.h"
#include "ui_widget.h"
#include <QString>
#include <QTime>
#include <QCalendarWidget>
#include <QDebug>
#include <QDate>
#include <QMessageBox>
#include <QPixmap>
#include <QIcon>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QFile ff;
    ff.remove("E:/Test/Down/天气.c");//刪除文件

    setWindowIconText(tr("万年历"));
    timerid = startTimer(1000);
    week[0] = " 星期一";
    week[1] = " 星期二";
    week[2] = " 星期三";
    week[3] = " 星期四";
    week[4] = " 星期五";
    week[5] = " 星期六";
    week[6] = " 星期日";
    //显示日期
    QCalendarWidget *calen = new QCalendarWidget;
    dat = calen->selectedDate();
    //calen->setSelectedDate(dat);
    int year = dat.year();
    int mon  = dat.month();
    int day  = dat.day();
    iweek=(day+2*mon+3*(mon+1)/5+year+year/4-year/100+year/400)%7;
    str_total = " "+QString::number(year)+"-"+QString::number(mon)+"-"+QString::number(day)+" ";
    ui->label_data->setText(str_total);
    //显示星期几
    ui->label_week->setText(week[iweek]);

    //图标显示图片
    QPixmap pixh(":/photo/home.jpg");
    QIcon iconh(pixh);
    ui->pushButton_today->setIcon(iconh);
    ui->pushButton_today->setIconSize(QSize(60,60));

    QPixmap pixs(":/photo/set.jpg");
    QIcon icons(pixs);
    ui->pushButton_set->setIcon(icons);
    ui->pushButton_set->setIconSize(QSize(60,60));

    QPixmap pixd(":/photo/delete.jpg");
    QIcon icond(pixd);
    ui->pushButton_clear->setIcon(icond);
    ui->pushButton_clear->setIconSize(QSize(40,40));

    QPixmap pixw(":/photo/where.jpg");
    QIcon iconw(pixw);
    ui->pushButton_where->setIcon(iconw);
    ui->pushButton_where->setIconSize(QSize(40,40));

}

void Widget::timerEvent(QTimerEvent *)
{
    //显示时间
        time = QTime::currentTime();
        str = time.toString("hh:mm:ss");
        ui->lcdNumber_time->display(str);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_set_clicked()
{
    Dialog *dia = new Dialog;
    connect(dia,SIGNAL(setDatestr(QString)),
            this,SLOT(getdatestr(QString)));
    connect(this,SIGNAL(setstr(QTime,QDate)),
            dia,SLOT(getstr(QTime,QDate)));
    emit setstr(time,dat);
    qDebug()<<"on_pushButton_set_clicked()";
    dia->exec();
}

void Widget::on_pushButton_today_clicked()
{
    ui->label_data->setText(str_total);
    //显示星期几
    ui->label_week->setText(week[iweek]);
}

void Widget::on_calendarWidget_clicked(const QDate &date)
{
    int year = date.year();
    int mon  = date.month();
    int day  = date.day();
    int cweek=(day+2*mon+3*(mon+1)/5+year+year/4-year/100+year/400)%7;
    QString str_cto = " "+QString::number(year)+"-"+QString::number(mon)+"-"+QString::number(day)+" ";
    ui->label_week->setText(week[cweek]);
    ui->label_data->setText(str_cto);
}

void Widget::getdatestr(QString sdatestr)
{
    datestr_w = datestr_w + sdatestr + "\n";
    ui->textBrowser->setText(datestr_w);
}

void Widget::on_pushButton_clear_clicked()
{
    //使用消息对话框提示用户是否真的需要修改
    QMessageBox::StandardButton rtn = QMessageBox::question(this,
                              "提示",//标题栏
                              "你确定要清空吗？",//显示的内容
                              QMessageBox::Yes | QMessageBox::No, //按钮的设置
                              QMessageBox::NoButton
                              );
    if(rtn == QMessageBox::Yes){
        ui->textBrowser->setText("");
        datestr_w = "";
    }
}

void Widget::getwether(QString weath)
{
    ui->lineEdit_city->setText(weath);
}

void Widget::on_pushButton_weather_restart_clicked()
{
    /*weather *wea = new weather;
    connect(wea,SIGNAL(setweather(QString)),
            this,SLOT(getwether(QString)));
    wea->exec();*/
    int i;
    //QString str = ":/gif/"+QString("%1".arg(i)+".png");
    QString str[4] = {":/photo/red.png",":/photo/black.png",":/photo/qing.png"
                     ,":/photo/sky.png"};
    for(i = 0; i<4; i++){
        QPixmap pix(str[i]);
        pix = pix.scaled(ui->label_weather_show->size());
        ui->label_weather_show->setPixmap(pix);
        qDebug()<<i;
        sleep(500);
    }
}

void Widget::on_pushButton_setweather_clicked()
{
    MainWindow *mainw = new MainWindow;
    connect(mainw,SIGNAL(set_return_city(QString)),
            this,SLOT(get_return_city(QString)));
    connect(mainw,SIGNAL(sendtemp(QString)),
            this,SLOT(showtemp(QString)));
    mainw->show();

}

void Widget::showtemp(QString temp)
{
    QFile ff("E:/Test/Down/天气.c");
    ff.resize(0);
    ui->label_temp->setText(temp);
}

void Widget::get_return_city(QString str_return_city)
{
    ui->lineEdit_city->setText(str_return_city);
}

void Widget::on_pushButton_where_clicked()
{
    weather *wea = new weather;
    wea->show();
}
