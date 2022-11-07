#ifndef MYDIR_H
#define MYDIR_H
#include<iostream>
#include<QStringList>
using namespace std;

class MyDir
{
    QStringList small_dir;
    int dir_count;
    QString dirpath;
public:
    MyDir(QString dirpath);

    QString getdirpath(){return dirpath;};
    int getdir_count()const{return dir_count;}
    QStringList getsmalldir()const{return small_dir;};
};

#endif // MYDIR_H
