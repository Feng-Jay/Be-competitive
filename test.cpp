#include <iostream>
using namespace std;

int main()
{
    // int mylist[2] = {1,2};
    // cout<<&mylist[1] - &mylist[0]<<endl;
    // cout << res<<endl; 
    struct test
    {
        int i;
        int j;
        char m;
    };
    test temp={1,2,3};
    cout<<&(temp.i)<<endl;
    cout<<&(temp.m)<<endl;
    cout<<&(temp.j)<<endl;
    cout<<sizeof(temp)<<endl;
}