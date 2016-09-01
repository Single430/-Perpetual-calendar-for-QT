#include "weather.h"
#include "ui_weather.h"

weather::weather( QWidget *parent) :
    QDialog(parent),
    ui(new Ui::weather)
{
    ui->setupUi(this);
    setWindowTitle("说明");
}

weather::~weather()
{
    delete ui;
}


