#include <iostream>
#include <unistd.h>
using namespace std;

struct test
{
    char name[10];
    int  x;
    int  y;
    char* ptr;
};

int main()
{
    short tell[10];
    cout<<tell<<" "<<tell+1<<endl;
    cout<<&tell<<" "<<&tell+1<<endl;
    int * temp;
    int temp1 =5;
    temp = & temp1;
    *temp = temp1;
    cout<< *temp << temp<<endl;
    char str[] = "fffff";
    test test1 = {"ffengjay", 21, 3, (char*)str};
    test test2 = test1;
    cout<< test2.name<<endl;
    test1.name[1]='G';
    cout<< test1.name<<endl;
    cout<< test2.name<<endl;
    cout<< test1.ptr<<" "<<test2.ptr<<endl;
    cout.setf(ios_base::fixed, ios_base::floatfield);
    float tub =10.0/3.0;
    double mint = 10.0/3.0;
    cout<<tub<<endl;
    cout<<mint<<endl;
    cout<<tub*10e6<<endl;
    cout<<mint*10e6<<endl;
    // double test = tub % mint;
    cout.put(88);
    int yams[3] {1,2,3};
    cout<<yams[0]<<yams[1]<<yams[2]<<endl;
    cout<<sizeof yams[0]<<endl;
    // cout<<yams<<endl;
}