#include <iostream>

using std::cout; using std::endl;
using std::cin;

int day[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

bool is_leap(int year){
    if (year%4==0 && year%100!=0)
        return true;
    if (year%400==0)
        return true;
    else return false;
}

int main()
{
    int year, month, days;
    while(cin>>year>>month>>days){
        int outcome=0;
        for(int i=0;i<month;i++)
            outcome+=day[i];
        if(month>2&&is_leap(year))
            outcome+=1;
        outcome+=days;
        cout<<outcome<<endl;
    }
}