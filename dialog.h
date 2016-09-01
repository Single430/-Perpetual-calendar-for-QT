#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTime>
#include <QDate>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void getstr(QTime sstr, QDate datq);

signals:
    void setDatestr(QString sdatestr);

private slots:
    void on_pushButto_sure_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
