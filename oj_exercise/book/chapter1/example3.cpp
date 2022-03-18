#include <iostream>
#include <cmath>
using namespace std;

bool is_leap(int year)
{
    return (year%4==0 && year%100!=0)||(year%400==0);
}
int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

int main()
{
    int year1, year2;
    while (cin>>year1>>year2){
        if(year1 > year2){
            swap(year1,year2);
        }
        int syear= year1/10000; int eyear=year2/10000;
        int smon = (year1%10000)/100; int emon = (year2%10000)/100;
        int sday = year1%100; int eday = year2%100;
        int res = 0;
        int days1=0;
        int days2=0;
        for (int i = smon; i<12; ++i){
            if(i==1){
                if (is_leap(syear)) days1+=29;
                else days1+=28;
            }else
            days1+=days[i];
        }
        if (smon==2&&is_leap(syear)){
            days1+=29-sday;
        }else days1+=days[smon-1]-sday;

        
        for (int i = 0; i<emon-1; ++i){
            if(i==1){
                if (is_leap(eyear)) days2+=29;
                else days2+=28;
            }else
            days2+=days[i];
        }
        days2+=eday;

        if (syear < eyear)
        {
            int gap = eyear - syear -1;
            res+=gap*365;
            int counter=0;
            for (int i = syear+1; i< eyear;++i){
                if(is_leap(i)) counter++;
            }
            res +=days1+days2+counter;
        }else{
            // cout<<days1<<days2;
            if(is_leap(syear))
            res = days2-366+days1;
            else res=days2-365+days1;
        }
        cout<<res<<endl;
    }    
}