#include <iostream>
#include <array>
using namespace std;

int main()
{
    char ch;
    int sum=0;
    if (sum ==0 and sum < 1)
    {
        cout<< "I use the and!\n";
    }
    while(cin>>ch)
    {
        if (ch == '0') break;
        sum += (ch - '0');
        cout << sum<<endl;
    }
}