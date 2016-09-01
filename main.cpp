#include "widget.h"
#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("simsun",8));
    Widget w;
    w.show();

    return a.exec();
}
