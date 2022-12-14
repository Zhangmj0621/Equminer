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
#include"filecontent.h"
#include"mydir.h"
#include<QListWidgetItem>
#include"equalfile.h"
#include"confirmerwidget.h"
#include<QTimer>
#include<QFile>
#include<QFileDialog>
#include<QUrl>
using namespace std;

QString strout;

Equalfile equalfile[200];

int equalnum=0;

bool ifequal[200];

Equalfile inequalfile[200];

int inequalnum=0;

string equalpath;
string inequalpath;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qInstallMessageHandler(logOutput);

    QFont qfont("Microsoft Yahei",14);
    ui->label->setFont(qfont);

    ui->label_2->setFont(qfont);

    ui->lineEdit->setFont(qfont);

    textEdit=new QTextEdit();

    textEdit->setParent(this);


    textEdit->setGeometry(360,30,301,331);


    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        QString string=QFileDialog::getExistingDirectory(this,"open","/home/oslab");

        ui->lineEdit->setText(string);
    });

    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QString dir_path=ui->lineEdit->text();
        init_dir.setPath(dir_path);
        if(!init_dir.exists())
        {
            QMessageBox::critical(this,"错误","请输入正确的路径！");
        }
        else
        {
            QString cz1="已成功打开文件夹"+dir_path;
            //QListWidgetItem* item1=new QListWidgetItem(cz1);
            //ui->listWidget->addItem(item1);
            qDebug()<<cz1;

            //QMessageBox::information(this,"true","判断成功，在文件中查看结果！");
            MyDir* mydir=new MyDir(dir_path);
            QDir up_dir=init_dir;
            up_dir.cdUp();
            QString up_dir_path=up_dir.absolutePath();
            //qDebug()<<up_dir_path;
            equalpath=up_dir_path.toStdString()+"/output/equal.csv";
            //qDebug()<<QString::fromStdString(equalpath);
            fstream equal_file(equalpath,ios::in | ios::out);
            inequalpath=up_dir_path.toStdString()+"/output/inequal.csv";
            fstream inequal_file(inequalpath,ios::in | ios::out);

            //对每个小dir进行操作
            for(int p=0;p<mydir->getdir_count();p++)
            {
                dir_path=mydir->getdirpath()+"/"+mydir->getsmalldir().at(p);
                //获得文件名称
                MyConfig config(dir_path);
                config.getnamelist();
                config.getinputbase();
                for(int i=0;i<config.readnamelist().size();i++)
                {
                    QString str=config.readnamelist().at(i);
                    //qDebug()<<str;
                }
                int maxnum=config.readnamelist().size();
                bool judge[20][20]; //用来暂存是否判断等价
                for(int i=0;i<maxnum;i++)
                    for(int j=0;j<maxnum;j++)
                        judge[i][j]=true;   //初始设定为等价，后续只要判断出现一次不等价就不必在进行接下去的判断
                for(int i=0;i<maxnum;i++)
                {
                    string tempnamelist=config.readnamelist().at(i).toStdString().substr(0,config.readnamelist().at(i).toStdString().size()-3);
                    tempnamelist+="o";
                    string temp="g++ -o "+dir_path.toStdString()+"/"+tempnamelist
                            +" "+dir_path.toStdString()+"/"+config.readnamelist().at(i).toStdString();
                    //qDebug()<<QString::fromStdString(temp);
                    system(temp.c_str());
                }
                //获得输入input.txt，进行十次判断
                Randomio randomio;
                string inputpath=dir_path.toStdString()+"/input.txt";
                fstream io_file;
                for(int k=0;k<10;k++)
                {
                    io_file.open(inputpath,ios::in | ios::out);
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
                            //qDebug()<<"int("<<a<<","<<b<<")";
                            int an=randomio.getrandomint(a,b);
                            io_file<<an;
                        }
                        else if(base[0]=='c')
                        {
                            char an=randomio.getrandomchar();
                            //qDebug()<<an;
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
                            //qDebug()<<QString::fromStdString(an);
                            io_file<<an;
                        }
                        if(i!=config.readinputBase().size()-1) io_file<<" ";
                    }
                    io_file.close();
                    //选取every文件运行得到结果
                    for(int i=0;i<maxnum;i++)
                    {
                        string tempnamelist=config.readnamelist().at(i).toStdString().substr(0,config.readnamelist().at(i).toStdString().size()-3);
                        string tempnamelist2=tempnamelist;
                        tempnamelist+="o";
                        tempnamelist2+="txt";
                        string temp=dir_path.toStdString()+"/"+tempnamelist+" <"+inputpath+" >"+dir_path.toStdString()+"/"+tempnamelist2;
                        //qDebug()<<QString::fromStdString(temp);
                        system(temp.c_str());
                    }
                    //两两比较判断是否相等
                    Filecontent* filecontent[100];
                    for(int i=0;i<maxnum;i++)
                    {
                        string tempnamelist=config.readnamelist().at(i).toStdString().substr(0,config.readnamelist().at(i).toStdString().size()-3);
                        tempnamelist+="txt";
                        Filecontent* temp=new Filecontent(dir_path.toStdString()+"/"+tempnamelist);
                        filecontent[i]=temp;
                        //qDebug()<<filecontent[i]->getstringnumber();
                        //qDebug()<<QString::fromStdString(tempnamelist)<<": " <<QString::fromStdString(filecontent[i]->getcontent().at(0));
                    }
                    for(int i=0;i<maxnum;i++)
                    {
                        for(int j=i+1;j<maxnum;j++)
                        {
                            if(judge[i][j]==false) continue;
                            else
                            {
                                bool temp=filecontent[i]->compare(filecontent[j]);
                                if(temp==false) judge[i][j]=false;
                            }

                        }
                    }


                }
                //print the answer

                for(int i=0;i<maxnum;i++)
                    for(int j=i+1;j<maxnum;j++)
                    {
                        if(judge[i][j]==true)
                        {
                            equal_file<<config.readnamelist().at(i).toStdString()<<","<<config.readnamelist().at(j).toStdString()
                                     <<endl;
                            equalfile[equalnum].file_ab1=dir_path+"/"+config.readnamelist().at(i);
                            equalfile[equalnum].file_ab2=dir_path+"/"+config.readnamelist().at(j);
                            equalfile[equalnum].file1=config.readnamelist().at(i);
                            equalfile[equalnum].file2=config.readnamelist().at(j);
                            equalnum++;
                        }
                        else
                        {
                            inequal_file<<config.readnamelist().at(i).toStdString()<<","<<config.readnamelist().at(j).toStdString()
                                     <<endl;
                            inequalfile[inequalnum].file_ab1=dir_path+"/"+config.readnamelist().at(i);
                            inequalfile[inequalnum].file_ab2=dir_path+"/"+config.readnamelist().at(j);
                            inequalfile[inequalnum].file1=config.readnamelist().at(i);
                            inequalfile[inequalnum].file2=config.readnamelist().at(j);
                            inequalnum++;
                        }
                    }
            }
            for(int i=0;i<equalnum;i++) ifequal[i]=true;
            equal_file.close();
            inequal_file.close();
            qDebug()<<"结果已生成，可至csv文件中查看!";
            qDebug()<<"";
            QTimer::singleShot(1000,this,[=](){
                ConfirmerWidget* confirmerwidget1=new ConfirmerWidget();
                confirmerwidget1->show();
            });

        }
    });
}

Widget::~Widget()
{
    delete ui;
}

Widget* Widget::getwidget(){
    static Widget windows;
    return &windows;
}

void Widget::logOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString text;
    //text.append(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + " ");


    text.append(msg);
    //strout=text;
    //textEdit->append(text);
    getwidget()->textEdit->append(text);
}

