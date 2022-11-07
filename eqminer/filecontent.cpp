#include "filecontent.h"
#include<fstream>
#include<QDebug>


Filecontent::Filecontent(string filepath)
{
    ifstream io_file(filepath,ios::in);
    string_number=0;
    if(!io_file)
    {
        qDebug()<<"文件打开失败";
    }
    string temp;

    while(!io_file.eof())
    {
        io_file>>temp;
        s.push_back(temp);
        string_number++;
    }
    io_file.close();
}

bool Filecontent::compare(const Filecontent* file)
{
    if(this->string_number!=file->string_number)
    {
        return false;
    }
    for(int i=0;i<string_number;i++)
    {
        if(this->s[i]!=file->s[i]) return false;
    }
    return true;
}
