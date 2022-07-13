// Done the first two chapter.
#include <iostream>
using namespace std;

void C2_p1();
long long C2_p2(int);
void C2_p4();

int main()
{
    cout << "This is FFengJay's summercamp!";
    cout << endl;   
    cout << "I will never forget this time!"<<endl;
    C2_p1();
    long long temp = C2_p2(100);
    cout<<temp<<endl;
    C2_p4();
}

void C2_p1()
{
    cout<<"Fengjie Li"<<endl;
    cout<<"Tianjin University"<<endl;
}

long long C2_p2(int len)
{
    return len*220;
}

void C2_p4()
{
    cout<<"Enter your age: ";
    int age;
    cin>>age;
    cout<<age*12<<endl;
}