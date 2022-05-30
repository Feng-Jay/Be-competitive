#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int n,m,g;

int main()
{
    cin>>n>>m;
    vector< vector< queue<int> > >all_area(m);
    int belong;
    for(int i=0; i<n; ++i){
        cin>> belong;
        all_area[belong].push_back({0});
    }


    cin>> g;
    vector<int> demands(6,0);
    for(int i=0; i<g;++i){
        for(int j=0; j<6;++j) cin>>demands[j];

    }

}