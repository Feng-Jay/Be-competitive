#include <iostream>
#include <algorithm>
using std::cin;
using std:: cout;
using std:: endl;

int main()
{
    int n;
    int mylist[100];
    while(cin>>n){
        for(int i =0; i<n; ++i)
            cin>>mylist[i];
        std::sort(mylist,mylist+n);
        for(int i=0; i<n; ++i)
            cout<<mylist[i]<<" ";
        cout<<endl;
    }
}