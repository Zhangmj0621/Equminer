#ifndef EQUALFILE_H
#define EQUALFILE_H
#include<iostream>
#include<QString>
using namespace std;

struct Equalfile{
    QString file1;
    QString file2;
    QString file_ab1;
    QString file_ab2;
};

extern Equalfile equalfile[200];
extern int equalnum;
extern bool ifequal[200];

extern Equalfile inequalfile[200];
extern int inequalnum;

extern string equalpath;

extern string inequalpath;


#endif // EQUALFILE_H
