#include "mydir.h"
#include<QDir>

MyDir::MyDir(QString dirpath)
{
    dir_count=0;
    this->dirpath=dirpath;
    QDir dir;
    dir.setPath(dirpath);
    //qDebug()<<dir.absolutePath();
    //dir.setPath(a.applicationDirPath());
    if (dir.exists())   //判断目录是否存在
    {
        QStringList dir_list = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);   //默认内部文件夹
        //QStringList file_list = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
        //仅获得.cpp文件
        this->small_dir=dir_list;
        this->dir_count=small_dir.size();
    }
}
