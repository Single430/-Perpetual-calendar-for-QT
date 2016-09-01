#ifndef WEATHER_H
#define WEATHER_H

#include <QDialog>
#include <QString>
#include <QObject>
#include <QtNetwork>
#include <QTimer>
#include <QByteArray>

namespace Ui {
class weather;
}

class weather : public QDialog
{
    Q_OBJECT

public:
    explicit weather(QWidget *parent = 0);
    ~weather();

signals:

public slots:

private slots:

private:
    Ui::weather *ui;

};

#endif // WEATHER_H
