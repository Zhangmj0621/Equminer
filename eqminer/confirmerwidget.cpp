#include "confirmerwidget.h"
#include "ui_confirmerwidget.h"
#include"equalfile.h"
#include"randomio.h"
#include<QFile>
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
    ui->lineEdit->setText(equalfile[zu].file1);
    ui->lineEdit_2->setText(equalfile[zu].file2);
    QFile file1(equalfile[zu].file1);
    QFile file2(equalfile[zu].file2);
    file1.open(QIODevice::ReadOnly);
    file2.open(QIODevice::ReadOnly);
    QByteArray array1=file1.readAll();
    QByteArray array2=file2.readAll();
    ui->textEdit->setText(array1);
    ui->textEdit_2->setText(array2);
    file1.close();
    file2.close();


    connect(ui->pushButton,&QPushButton::clicked,[=](){
        judgenum++;
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
            QFile file1(equalfile[zu].file1);
            QFile file2(equalfile[zu].file2);
            file1.open(QIODevice::ReadOnly);
            file2.open(QIODevice::ReadOnly);
            QByteArray array1=file1.readAll();
            QByteArray array2=file2.readAll();
            ui->textEdit->setText(array1);
            ui->textEdit_2->setText(array2);
            file1.close();
            file2.close();
        }

    });

    connect(ui->pushButton_2,&QPushButton::clicked,[=](){

    });


}

ConfirmerWidget::~ConfirmerWidget()
{
    delete ui;
}
