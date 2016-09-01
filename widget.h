#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QTime>
#include <QDate>
#include <QCoreApplication>
#include <QEventLoop>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void sleep(unsigned int msec)
    {
        QTime dieTime = QTime::currentTime().addMSecs(msec);
        while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

protected:
    void timerEvent(QTimerEvent *);//定时处理函数

public slots:
    void getdatestr(QString sdatestr);
    void getwether(QString weath);
    void get_return_city(QString str_return_city);
    void showtemp(QString temp);

signals:
    void setstr(QTime sstr,QDate datq);

private slots:

    void on_pushButton_set_clicked();

    void on_pushButton_today_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_pushButton_clear_clicked();

    void on_pushButton_setweather_clicked();

    void on_pushButton_weather_restart_clicked();

    void on_pushButton_where_clicked();

private:
    Ui::Widget *ui;
    int timerid;
    QString str;
    QString str_total;
    QString week[7];
    int iweek;
    QString datestr_w;
    QTime time;
    QDate dat;
};

#endif // WIDGET_H
