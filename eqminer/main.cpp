#include "widget.h"

#include <QApplication>
#include"myconfig.h"
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir init_dir;
    QDir temp_dir;
    temp_dir.setPath(a.applicationDirPath());
    qDebug()<<temp_dir.absoluteFilePath("input/4A");

    //textEdit->show();
    Widget::getwidget()->show();
    return a.exec();
}
