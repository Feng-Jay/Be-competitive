#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n,k;
int main()
{
    cin>>n>>k;
    int xi,yi;
    vector<int> initialized;
    initialized.push_back(0);
    int ans=0;
    for(int i=0; i<k; ++i){
        cin>>xi>>yi;
        if(find(initialized.begin(),initialized.end(),yi)==initialized.end()){
            ans++;   
        }
        initialized.push_back(xi);
    }    
    cout<<ans<<endl;
}