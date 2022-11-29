#ifndef EQUALFILE_H
#define EQUALFILE_H
#include<iostream>
#include<QString>
using namespace std;

struct Equalfile{
    QString file1;
    QString file2;
};

extern Equalfile equalfile[100];
extern int equalnum;

#endif // EQUALFILE_H
