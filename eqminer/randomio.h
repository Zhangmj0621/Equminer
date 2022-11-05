#ifndef RANDOMIO_H
#define RANDOMIO_H
#include<iostream>
using namespace std;

class Randomio
{
public:
    Randomio();

    int getrandomint(int a,int b);
    char getrandomchar();
    string getrandomstring(int a,int b);

    int splitrandom(string base);
};

#endif // RANDOMIO_H
