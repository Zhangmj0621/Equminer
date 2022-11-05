#include "randomio.h"
#include<QRandomGenerator>

Randomio::Randomio()
{

}

int Randomio::getrandomint(int a,int b)
{
    return QRandomGenerator::global()->bounded(a, b);
}

char Randomio::getrandomchar()
{
    int temp=QRandomGenerator::global()->bounded(0, 1);
    if(temp==0) return 'a'+QRandomGenerator::global()->bounded(0, 25);
    else return 'A'+QRandomGenerator::global()->bounded(0, 25);
}

string Randomio::getrandomstring(int a,int b)
{
    string temp;
    int len=QRandomGenerator::global()->bounded(a, b);
    for(int i=0;i<len;i++)
    {
        temp.push_back(getrandomchar());
    }
    return temp;
}

int Randomio::splitrandom(string base)
{

}
