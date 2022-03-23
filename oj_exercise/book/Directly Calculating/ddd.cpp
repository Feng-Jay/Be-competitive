#include <iostream>

using std::cout; using std::endl;

using std::cin;

char mylist[80][80];

int main()
{
    int n;
    char center;
    char outer;
    while(cin>>n>>center>>outer){
        char c;
        for(int i=0; i<(n/2)+1; ++i){
            c = i%2 ? center : outer;
            for(int j=0;j<n-2*i;++j){
                mylist[i][i+j]=c;//up
                mylist[i+j][i]=c;//left
                mylist[j+i][n-i-1]=c;//right
                mylist[n-i-1][i+j]=c;//down
            }
        }
        if(n!=1){
            mylist[0][0]=' ';
            mylist[n-1][n-1]=' ';
            mylist[0][n-1]=' ';
            mylist[n-1][0]=' ';
        }
        
        for(int i=0;i<n;++i){
            for(int j=0; j<n; ++j){
                cout<<mylist[i][j];
            }
            cout<<endl;
        }
    }
}