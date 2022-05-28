#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int n,m,k;
    cin>>n>>m>>k;
    vector<int> enter(4e5+5, 0);
    for(int i=0; i<n; ++i){
        int temp1, temp2;
        cin>>temp1>>temp2;
        enter[temp1-temp2+1 >0?(temp1-temp2+1):1] +=1;
        enter[temp1+1] -=1;
    }
    for(int i=1; i<4e5+5;++i){
        enter[i] += enter[i-1];
    }
    int request;
    for(int i=0;i<m;++i){
        cin>>request;
        cout<<enter[request+k]<<endl;
    }

}