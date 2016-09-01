#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QTimer>
#include <QByteArray>
#include <QTextCodec>
#include <QDesktopServices>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QCoreApplication>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    typedef struct{
        QString city;
        QString cityid;
        QString temp1;
        QString temp2;
        QString weather1;
        QString weather2;
        QString wind1;
        QString wind2;
        QString index;
        QString index_d;
        QString index48;
        QString index48_d;
        QString index_xc;  //洗车指数
        QString index_ls;  //晾晒
        QString index_ag;  //过敏
        QString index_tr;   //旅游
        QString index_uv;  //紫外线
        QString date_y;  //日期
        QString week;   //星期
        //QString img_title1;
       // QString img_title2;
    }weatherdata;
    weatherdata data;


private slots:
    void on_comboBox_activated(const QString &arg1);
    void on_OK_clicked();
    void on_Cancel_clicked();

public slots:
    void readHtml(QNetworkReply *reply);
    void readyRead();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downFinished();

signals:
    void set_return_city(QString str_return_city);
    void setHtmldate(QString html);
    void sendtemp(QString temp);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manage;
    QNetworkReply *manReply;
    QEventLoop loop;
    QByteArray responseData;
    QFile *file;


};

#endif // MAINWINDOW_H
