#include "widget.h"
#include "ui_widget.h"
#include"myconfig.h"
#include<QPushButton>
#include<QFont>
#include<QMessageBox>
#include<QDebug>
#include"randomio.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QFont qfont("Microsoft Yahei",14);
    ui->label->setFont(qfont);

    ui->label_2->setFont(qfont);

    ui->lineEdit->setFont(qfont);

    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QString dir_path=ui->lineEdit->text();
        init_dir.setPath(dir_path);
        if(!init_dir.exists())
        {
            QMessageBox::critical(this,"错误","请输入正确的路径！");
        }
        else
        {
            //获得文件名称
            MyConfig config(dir_path);
            config.getnamelist();
            config.getinputbase();
            for(int i=0;i<config.readnamelist().size();i++)
            {
                QString str=config.readnamelist().at(i);
                qDebug()<<str;
            }
            int maxnum=config.readnamelist().size();
            bool judge[maxnum][maxnum]; //用来暂存是否判断等价
            for(int i=0;i<maxnum;i++)
                for(int j=0;j<maxnum;j++)
                    judge[i][j]=true;   //初始设定为等价，后续只要判断出现一次不等价就不必在进行接下去的判断
            //获得输入input.txt，进行十次判断
            Randomio randomio;
            fstream io_file(dir_path.toStdString()+"/input.txt",ios::in | ios::out);
            for(int k=0;k<9;k++)
            {
                for(int i=0;i<config.readinputBase().size();i++)
                {
                    QString base=config.readinputBase().at(i);
                    if(base[0]=='i')
                    {
                        int a=0;
                        int i=4;
                        for(;i<base.size();i++)
                        {
                            if(base[i]!=',')
                            {
                                a=a*10+(base.toStdString()[i]-'0');
                            }
                            else break;
                        }
                        int b=0;
                        for(i=i+1;i<base.size()-1;i++)
                        {
                            b=b*10+base.toStdString()[i]-'0';
                        }
                        int an=randomio.getrandomint(a,b);
                        io_file<<an;
                    }
                    else if(base[0]=='c')
                    {
                        char an=randomio.getrandomchar();
                        io_file<<an;
                    }
                    else
                    {
                        int a=0;
                        int i=7;
                        for(;i<base.size();i++)
                        {
                            if(base[i]!=',')
                            {
                                a=a*10+(base.toStdString()[i]-'0');
                            }
                            else break;
                        }
                        int b=0;
                        for(i=i+1;i<base.size()-1;i++)
                        {
                            b=b*10+base.toStdString()[i]-'0';
                        }
                        string an=randomio.getrandomstring(a,b);
                        io_file<<an;
                    }
                    if(i!=config.readinputBase().size()-1) io_file<<" ";
                }
                //选取两个文件运行得到结果
                for(int i=0;i<maxnum;i++)
                {
                    string temp="gcc "+dir_path.toStdString()+"/"+config.readnamelist().at(i).toStdString();
                    system(temp.c_str());
                }
            }


        }
    });
}

Widget::~Widget()
{
    delete ui;
}

