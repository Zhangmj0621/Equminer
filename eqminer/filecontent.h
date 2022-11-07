#ifndef FILECONTENT_H
#define FILECONTENT_H
#include<iostream>
#include<vector>
using namespace std;

class Filecontent
{
    int string_number;
    vector<string> s;
public:
    Filecontent(string filepath);

    int getstringnumber()const{return string_number;};

    vector<string> getcontent()const{
        return s;
    }


    bool compare(const Filecontent* file);
};

#endif // FILECONTENT_H
