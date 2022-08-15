// Created on 可爱的熊.

#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <ctime>
#include <cstdlib>
using namespace std;

const int ininum = 13;
const int mixtimes = 50;

struct card {
    int num,color;
};

struct result {
    int winner = -1;
    int At = 0;  //A出一次牌记为一次
    int Bt = 0;  //B出一次牌记为一次
};

queue<card> A,B;

//初始随机发牌
void iniHandOut(int ran) {
    A = queue<card>();
    B = queue<card>();
    card tmp;
    for(int i=0;i<4;i++) {
        for(int j=1;j<=ininum;j++) {
            tmp.num = j;
            tmp.color = i;
            switch(ran%2) {
                case 0: if(A.size()<2*ininum) {
                            A.push(tmp);
                            break;
                        }
                        else {
                            B.push(tmp);
                            break;
                        }
                case 1: if(B.size()<2*ininum) {
                            B.push(tmp);
                            break;
                        }
                      else {
                            A.push(tmp);
                            break;
                        }
            }
            //srand(ran);
            ran = rand();
        }
    }
    return;
}

//输出两人手中的牌
void output(queue<card> A1,queue<card> B1) {
    cout<<"A:"<<endl;
    for(int i=0;i<A.size();i++) {
        cout<<A1.front().num<<";"<<A1.front().color<<" ";
        A1.pop();
    }
    cout<<endl<<"B:"<<endl;
    for(int i=0;i<B.size();i++) {
        cout<<B1.front().num<<";"<<B1.front().color<<" ";
        B1.pop();
    }
    cout<<endl;
    return;
}

//打乱
void mixup(queue<card>& T) {
    int size = T.size();
    queue<card> tmp = T;
    int tmp_num[size],tmp_color[size];
    int begin,length;
    bool rem[size];
    for(int i=0;i<mixtimes;i++) {
        for(int j=0;j<size;j++) rem[j] = 0;
        for(int j=0;j<size;j++) {
            tmp_num[j] = tmp.front().num;
            tmp_color[j] = tmp.front().color;
            tmp.pop();
        }
        begin = rand()%size;
        length = rand()%(size-begin);
        card t;
        for(int j=begin;j<(begin+length);j++) {
            t.num = tmp_num[j];
            t.color = tmp_color[j];
            tmp.push(t);
            rem[j] = 1;
        }
        for(int j=0;j<size;j++) {
            if(!rem[j]) {
                t.num = tmp_num[j];
                t.color = tmp_color[j];
                tmp.push(t);
            }
        }
    }
    T = tmp;
    return;
}

//游戏过程
result game() {
    result re;  //记录次数和最终结果
    bool ca[13]={0,0,0,0,0, 0,0,0,0,0, 0,0,0};   //记录桌面上存在的纸牌
    stack<card> desk = stack<card>();
    card tmp;
    while(A.size()>0&&B.size()>0) {
        Aa: re.At++;
        mixup(A);
        tmp = A.front();
        A.pop();
        if(ca[tmp.num-1]) {
            A.push(tmp);
            while(desk.top().num!=tmp.num) {
                A.push(desk.top());
                ca[desk.top().num-1] = 0;
                desk.pop();
            }
            A.push(desk.top());
            ca[desk.top().num-1] = 0;
            desk.pop();
            goto Aa;
        }
        else {
            desk.push(tmp);
            ca[desk.top().num-1] = 1;
        }

        Bb: re.Bt++;
        mixup(B);
        tmp = B.front();
        B.pop();
        if(ca[tmp.num-1]) {
            B.push(tmp);
            while(desk.top().num!=tmp.num) {
                B.push(desk.top());
                ca[desk.top().num-1] = 0;
                desk.pop();
            }
            B.push(desk.top());
            ca[desk.top().num-1] = 0;
            desk.pop();
            goto Bb;
        }
        else {
            desk.push(tmp);
            ca[desk.top().num-1] = 1;
        }
    }
    if(A.size()==0) re.winner = 1;
    else if(B.size()==0) re.winner = 0;
    else re.winner = 2;
    return re;
}

int main() {
    srand(time(0));
    for(int e=0;e<GAME;e++){
    iniHandOut(rand());
    //output(A,B);
    mixup(A);
    mixup(B);
    //output(A,B);
    result res = game();
    //cout<<"-----------"<<endl<<"Winner:"<<res.winner<<endl<<"Times:"<<endl<<"A:"<<res.At<<endl<<"B:"<<res.Bt<<endl<<"ALL:"<<res.At+res.Bt;
    cout<<res.At+res.Bt<<" ";}
    return 0;
}