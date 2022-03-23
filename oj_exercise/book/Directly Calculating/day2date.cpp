#include<iostream>
#include <iomanip>
using std::cin; using std::cout;
using std::endl;

int day[2][13]={{0,31,28,31,30,31,30,31,31,30,31,30,31},
{0,31,29,31,30,31,30,31,31,30,31,30,31}
};

bool is_leap(int year){
    if (year%4==0 && year%100!=0)
        return true;
    if (year%400==0)
        return true;
    else return false;
}


int main()
{
    int year, days;
    
    while(cin>>year>>days){
        int o_m=0;
        int o_d=0;
        int d_2=0;
        d_2 = is_leap(year) ? 1 : 0;
        while(days-day[d_2][o_m]>0){
            days-=day[d_2][o_m];
            ++o_m;
            // cout<<"loop"<<endl;
        }
        // cout<<"s"<<endl;
        cout<<std::setw(4)<<std::setfill('0')<<year<<"-"<<std::setw(2)<<o_m<<"-"<<std::setw(2)<<days<<endl;
    }
}