#include "confirmerwidget.h"
#include "ui_confirmerwidget.h"
#include"equalfile.h"
#include"randomio.h"
#include<QFile>
#include<iostream>
using namespace std;
#include<fstream>
#include<QMessageBox>

int zu;
bool* tempjudge;
int judgenum=0;

ConfirmerWidget::ConfirmerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfirmerWidget)
{
    ui->setupUi(this);

    //随机选取五个等价组进行抽查
    tempjudge=new bool[equalnum];
    for(int i=0;i<equalnum-1;i++) tempjudge[i]=false;
    Randomio randomio;

    zu=randomio.getrandomint(0,equalnum-1);
    while(tempjudge[zu]){
        zu=randomio.getrandomint(0,equalnum-1);
    }
    tempjudge[zu]=true;
    //ui->textEdit->setTextColor(QColor(Qt::black));
    ui->lineEdit->setText(equalfile[zu].file1);
    ui->lineEdit_2->setText(equalfile[zu].file2);
    QFile file1(equalfile[zu].file_ab1);
    QFile file2(equalfile[zu].file_ab2);
    file1.open(QIODevice::ReadOnly);
    file2.open(QIODevice::ReadOnly);
    QByteArray array1;
    QByteArray array2;

    while(!file1.atEnd()||!file2.atEnd())
    {
        if(!file1.atEnd()||!file2.atEnd()){
            QByteArray temp1=file1.readLine();
            QByteArray temp2=file2.readLine();
            if(temp1!=temp2)
            {
                ui->textEdit->setTextColor(QColor(Qt::red));
                ui->textEdit->append(temp1);
                ui->textEdit_2->append(temp2);
                ui->textEdit->setTextColor(QColor(Qt::black));
            }
            else
            {
                ui->textEdit->append(temp1);
                ui->textEdit_2->append(temp2);
            }
        }
        else if(!file1.atEnd())
        {
            QByteArray temp1=file1.readLine();
            ui->textEdit->setTextColor(QColor(Qt::red));
            ui->textEdit->append(temp1);
            ui->textEdit->setTextColor(QColor(Qt::black));
        }
        else{
            QByteArray temp2=file2.readLine();
            ui->textEdit_2->setTextColor(QColor(Qt::red));
            ui->textEdit_2->append(temp2);
            ui->textEdit_2->setTextColor(QColor(Qt::black));
        }
    }

    //ui->textEdit->setText(array1);
    //ui->textEdit_2->setText(array2);

    file1.close();
    file2.close();


    connect(ui->pushButton,&QPushButton::clicked,[=](){
        judgenum++;
        ui->textEdit->clear();
        ui->textEdit_2->clear();
        if(judgenum==5)
        {
            QMessageBox::information(this,"true","您已完成等价确认！");
            this->close();
            return;
        }
        else
        {
            QMessageBox::information(this,"true","即将给您展示下一组需要确认的程序对!");
            Randomio randomiotemp;
            while(tempjudge[zu]){
                zu=randomiotemp.getrandomint(0,equalnum-1);
            }
            tempjudge[zu]=true;
            ui->lineEdit->setText(equalfile[zu].file1);
            ui->lineEdit_2->setText(equalfile[zu].file2);
            QFile file1(equalfile[zu].file_ab1);
            QFile file2(equalfile[zu].file_ab2);
            file1.open(QIODevice::ReadOnly);
            file2.open(QIODevice::ReadOnly);
            while(!file1.atEnd()||!file2.atEnd())
            {
                if(!file1.atEnd()||!file2.atEnd()){
                    QByteArray temp1=file1.readLine();
                    QByteArray temp2=file2.readLine();
                    if(temp1!=temp2)
                    {
                        ui->textEdit->setTextColor(QColor(Qt::red));
                        ui->textEdit->append(temp1);
                        ui->textEdit_2->append(temp2);
                        ui->textEdit->setTextColor(QColor(Qt::black));
                    }
                    else
                    {
                        ui->textEdit->append(temp1);
                        ui->textEdit_2->append(temp2);
                    }
                }
                else if(!file1.atEnd())
                {
                    QByteArray temp1=file1.readLine();
                    ui->textEdit->setTextColor(QColor(Qt::red));
                    ui->textEdit->append(temp1);
                    ui->textEdit->setTextColor(QColor(Qt::black));
                }
                else{
                    QByteArray temp2=file2.readLine();
                    ui->textEdit_2->setTextColor(QColor(Qt::red));
                    ui->textEdit_2->append(temp2);
                    ui->textEdit_2->setTextColor(QColor(Qt::black));
                }
            }
            file1.close();
            file2.close();
        }

    });

    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        judgenum++;
        ui->textEdit->clear();
        ui->textEdit_2->clear();
        ifequal[zu]=false;
        inequalfile[inequalnum]=equalfile[zu];
        inequalnum++;
        ofstream equal_file(equalpath,ios::out);
        ofstream inequal_file(inequalpath,ios::out);
        for(int i=0;i<equalnum;i++)
        {
            if(ifequal[i])
            {
                equal_file<<equalfile[i].file1.toStdString()<<","<<equalfile[i].file2.toStdString()<<endl;
            }
        }
        for(int i=0;i<inequalnum;i++)
        {
            inequal_file<<inequalfile[i].file1.toStdString()<<","<<inequalfile[i].file2.toStdString()<<endl;
        }
        equal_file.close();
        inequal_file.close();
        if(judgenum==5)
        {
            QMessageBox::information(this,"true","您已完成等价确认！");
            this->close();
            return;
        }
        else
        {
            QMessageBox::information(this,"true","即将给您展示下一组需要确认的程序对!");
            Randomio randomiotemp;
            while(tempjudge[zu]){
                zu=randomiotemp.getrandomint(0,equalnum-1);
            }
            tempjudge[zu]=true;
            ui->lineEdit->setText(equalfile[zu].file1);
            ui->lineEdit_2->setText(equalfile[zu].file2);
            QFile file1(equalfile[zu].file_ab1);
            QFile file2(equalfile[zu].file_ab2);
            file1.open(QIODevice::ReadOnly);
            file2.open(QIODevice::ReadOnly);
            while(!file1.atEnd()||!file2.atEnd())
            {
                if(!file1.atEnd()||!file2.atEnd()){
                    QByteArray temp1=file1.readLine();
                    QByteArray temp2=file2.readLine();
                    if(temp1!=temp2)
                    {
                        ui->textEdit->setTextColor(QColor(Qt::red));
                        ui->textEdit->append(temp1);
                        ui->textEdit_2->append(temp2);
                        ui->textEdit->setTextColor(QColor(Qt::black));
                    }
                    else
                    {
                        ui->textEdit->append(temp1);
                        ui->textEdit_2->append(temp2);
                    }
                }
                else if(!file1.atEnd())
                {
                    QByteArray temp1=file1.readLine();
                    ui->textEdit->setTextColor(QColor(Qt::red));
                    ui->textEdit->append(temp1);
                    ui->textEdit->setTextColor(QColor(Qt::black));
                }
                else{
                    QByteArray temp2=file2.readLine();
                    ui->textEdit_2->setTextColor(QColor(Qt::red));
                    ui->textEdit_2->append(temp2);
                    ui->textEdit_2->setTextColor(QColor(Qt::black));
                }
            }
            file1.close();
            file2.close();
        }

    });


}

ConfirmerWidget::~ConfirmerWidget()
{
    delete ui;
}
