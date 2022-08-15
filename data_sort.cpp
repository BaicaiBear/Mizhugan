// Created on 可爱的熊.

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <fstream>

#define NUM 200000
using namespace std;

fstream ofs;
fstream ifs;

int main() {
    ofs.open("/www/wwwroot/bearcabbage.top/output-s.html",ios::out);
    ifs.open("/www/wwwroot/bearcabbage.top/output.html",ios::in);
    int data[NUM];
    for(int i=0;i<NUM;i++)
        ifs>>data[i];
    sort(data,data+NUM);
    for(int i=0;i<NUM;i++)
        ofs<<data[i]<<" ";
    ofs.close();
    ifs.close();
    return 0;
}