#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QTime>
#include <QDate>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("设置提醒"));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButto_sure_clicked()
{
    //使用消息对话框提示用户是否真的需要修改
    QMessageBox::StandardButton rtn = QMessageBox::question(this,
                              "提示",//标题栏
                              "你确定要设置吗？",//显示的内容
                              QMessageBox::Yes | QMessageBox::No, //按钮的设置
                              QMessageBox::NoButton
                              );
    if(rtn == QMessageBox::Yes){
        QString datestr = ui->dateTimeEdit->text();
        datestr = datestr + " : " + ui->lineEdit->text();
        emit setDatestr(datestr);
    }
    accept();
}

void Dialog::getstr(QTime sstr, QDate datq)
{
    ui->dateTimeEdit->setTime(sstr);
    ui->dateTimeEdit->setDate(datq);
}

void Dialog::on_pushButton_cancel_clicked()
{
    reject();
}
