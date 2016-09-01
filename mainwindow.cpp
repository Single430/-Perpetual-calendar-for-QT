#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("设置城市"));

    manage = new QNetworkAccessManager(this);
    connect(manage,SIGNAL(finished(QNetworkReply*)),
            this,SLOT(readHtml(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    ui->comboBox_1->clear();
    QStringList list;
    list = arg1.split(' ');
    QFile f(":/photo/citycode.txt");

    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<f.errorString();
    }
    f.seek(0);
    QTextStream in(&f);
    while(!in.atEnd()){
            QString line = in.readLine().trimmed();
            if(line.left(5) == list.at(1))
            {
                qDebug()<<line;
                ui->comboBox_1->addItem(line);
            }
    }
    f.close();
}

void MainWindow::on_OK_clicked()
{
    QString str_get;
    str_get = ui->comboBox_1->currentText();

    QString str_city = str_get.section("=",1,1);
    qDebug()<<"str_city"<<str_city;
    emit set_return_city(str_city);

    str_get= str_get.split("=").at(0);
    qDebug()<<"str_get"<<str_get;

    QString html = "http://www.weather.com.cn/weather1d/" + str_get + ".shtml#search";
    qDebug()<<"HTML"<<html;

    QUrl url;
    url.setUrl(html);
    QNetworkRequest request(url);
    manReply = manage->get(request);
    connect(manReply,SIGNAL(readyRead()),
            this,SLOT(readyRead()));
    connect(manReply,SIGNAL(downloadProgress(qint64,qint64)),
                this,SLOT(downloadProgress(qint64,qint64)));
    connect(manReply,SIGNAL(finished()),this,SLOT(downFinished()));

    this->close();

}

void MainWindow::readyRead()
{
    QFileInfo fileinfo(manReply->url().path());
    QString thefileName = fileinfo.fileName().isEmpty()?"index.html":"天气.c";//fileinfo.fileName();
    QString thePath ="E:/Test/Down/";
    QDir createfile;
    bool exist = createfile.exists(thePath);
    if(!exist)
    {
        createfile.mkpath(thePath);
    }
    thePath += thefileName;
    file=new QFile(thePath);

    if(file->open(QIODevice::Append))
    {
        file->write(manReply->readAll());//写进file
        file->flush();
    }
}

void MainWindow::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug()<<"Total:  "<<bytesTotal<<"  current received : "<<bytesReceived;
}

void MainWindow::downFinished()
{
    qDebug()<<"=======";
    file->flush();
    file->close();
    delete file;

    QFile weather_file("E:/Test/Down/天气.c");

    if(!weather_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<weather_file.errorString();
    }
    weather_file.seek(0);
    QTextStream in(&weather_file);
    while(!in.atEnd()){
            QString line = in.readLine().trimmed();
            //qDebug()<<line;
            QString line_file = line.section("id=",1,20);
            QString line_file2 = line_file.section("hidden_title",1,1);
            QString line_file3 = line_file2.section("value=",1,1);
            QString line_file1 = line_file3.section("/",1,1);
            if(line_file1 != ""){
                qDebug()<<":"<<line_file1;
                emit sendtemp(line_file1);
            }

    }
    qDebug()<<"OK!";
    weather_file.close();
}


void MainWindow::readHtml(QNetworkReply *reply)
{
    //查看是否有错误
    switch(reply->error())
    {
        //如果没有错误把页面输出
        case QNetworkReply::NoError:
            {
                qDebug()<<"no error";
                QTextCodec * cod=QTextCodec::codecForName("utf-8");
                QString str=cod->toUnicode(reply->readAll());
                //qDebug()<<str;
            }
            break;
        case QNetworkReply::ContentNotFoundError:
            {
                QUrl failedUrl;
                failedUrl = reply->request().url();
                int httpStatus = reply->attribute(
                            QNetworkRequest::HttpStatusCodeAttribute).toInt();
                QString reason = reply->attribute( QNetworkRequest::HttpReasonPhraseAttribute ).toString();
                qDebug()<<"url"<<failedUrl <<httpStatus<<"   "<<reason;
            }
            break;
        default:
            {
                qDebug()<<"Have error"<<reply->errorString()<<" error "<<reply->error();
            }
    }
    qDebug()<<"finished";
}

void MainWindow::on_Cancel_clicked()
{
    this->close();
}
