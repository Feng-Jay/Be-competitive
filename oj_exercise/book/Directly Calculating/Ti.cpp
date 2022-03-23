#include <iostream>

using std::cin;
using std::cout; using std::endl;

int main(){
    int h;
    while (cin>>h)
    {
        int bottom=3*h-2;
        for(int i=0;i<h;++i){
            for(int j=0;j<bottom; ++j){
                if (j<bottom-h-2*i)
                    cout<<" ";
                else 
                    cout<<"*";
            }
            cout<<endl;
        }
    }
    

}