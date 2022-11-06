#include "myconfig.h"
#include<QDir>
#include<QDebug>
#include<fstream>
#include<iostream>
using namespace std;

MyConfig::MyConfig(QString dirname)
{
    fileCount=0;
    this->dirPath=dirname;
}

void MyConfig::getnamelist()
{
    QDir dir;
    dir.setPath(dirPath);
    qDebug()<<dir.absolutePath();
    //dir.setPath(a.applicationDirPath());
    if (dir.exists())   //判断目录是否存在
    {
        //QStringList dir_list = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);   //默认没有内部文件夹
        //QStringList file_list = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
        //仅获得.cpp文件
        QStringList nameFilters;
        nameFilters << "*.cpp";
        QStringList file_list_spec = dir.entryList(nameFilters, QDir::Files | QDir::NoDotAndDotDot);
        this->namelist=file_list_spec;
    }
}

QStringList MyConfig::readnamelist(){
    return this->namelist;
}

void MyConfig::getinputbase()
{
    fstream io_file(dirPath.toStdString()+"/stdin_format.txt",ios::in | ios::out);
    if(!io_file)
    {
        qDebug()<<"文件打开失败";
        return;
    }
    string temp[20];
    int i=0;
    string s;

    while(!io_file.eof())
    {
        io_file>>s;
        temp[i]=s;
        i++;
    }
    for(int j=0;j<i;j++)
    {
        qDebug()<<QString::fromStdString(temp[j]);
        this->inputBase.push_back(QString::fromStdString(temp[j]));
    }
    io_file.close();
}

QStringList MyConfig::readinputBase(){
    return this->inputBase;
}
