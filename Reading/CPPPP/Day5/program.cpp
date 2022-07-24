#include <iostream>

using namespace std;

void test1(const char*, int = 1);
void test1(const char*);
int main()
{
    char mylist[] = "this is ffengjay";
    test1(mylist);
}
void test1(const char* str, int m)
{
    cout<<"I'm the default func ";
    cout << *(str+m)<<endl;
}

void test1(const char* str)
{
    cout<<"I'm the normal func ";
    cout<<*(str)<<endl;
}