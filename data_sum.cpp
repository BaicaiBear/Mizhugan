// Created on 可爱的熊.

#include <iostream>
#include <cstdio>
#include <numeric>
#include <algorithm>
#include <queue>
#include <fstream>

#define NUM 200000
using namespace std;

fstream ofs;
fstream ifs;

int main() {
    ifs.open("/www/wwwroot/bearcabbage.top/output-s.html",ios::in);
    ofs.open("/www/wwwroot/bearcabbage.top/output-d.html",ios::out);
    int data[NUM];
    queue<int> da = queue<int>();
    for(int i=0;i<NUM;i++) {
        ifs>>data[i];
        da.push(data[i]);
    }
    int size = data[NUM-1]/10+1;
    //cout<< (double)accumulate(data,data+NUM,0)/(double)NUM;
    int tj[size];
    for(int i=0;i<size;i++) tj[i] = 0;
    for(int i=0;i<size;i++) {
        while(da.front()<(i+1)*10 && da.front()>=i*10) {
            tj[i]++;
            da.pop();
        }
    }
    ofs<<"----------------"<<endl;
    for(int i=0;i<size;i++) ofs<<tj[i]<<",";
    return 0;
}