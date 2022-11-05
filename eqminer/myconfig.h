#ifndef MYCONFIG_H
#define MYCONFIG_H
#include<QStringList>
#include<QDir>

static QDir init_dir;

class MyConfig
{
    QString dirPath;    //to save the dir name
    int fileCount;  //to save the file count
    QStringList namelist;  //to save the filename
    QStringList inputBase;  //to save the base of input

public:
    MyConfig(QString);

    QStringList readnamelist();
    QStringList readinputBase();

    void getnamelist();
    void getinputbase();
};

#endif // MYCONFIG_H
