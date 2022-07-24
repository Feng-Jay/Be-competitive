#include  <iostream>
#include <fstream>

using namespace std;

void test(void)
{
    cout<<"This is the pf's out\n";
}

int main()
{
    char automobile[50];
    int year;
    double a_price, b_price;
    void (*pf)(void);
    pf = test;
    pf();
    (*pf)();
    ofstream outFile;
    outFile.open("./test.txt");
    cout<<"Enter the make and model of automobile: \n";
    cin.getline(automobile,50);
    cout<<"Enter the model year: \n";
    cin>>year;
    cout<<"Enter the original asking price: \n";
    cin>>a_price;
    b_price = 0.913 * a_price;
    outFile << automobile << endl;
    outFile << year << endl;
    outFile << a_price << endl;
    outFile.close();
    return 0;
}