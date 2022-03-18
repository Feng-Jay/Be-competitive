#include <iostream>
#include <string>
#include <algorithm>

using std:: cin;
using std:: cout;
using std:: endl;
using std:: sort;
using std:: string;

class Student{
    public: 
    string name;
    int age;
    double score;
    // Student():name("test"),age(20),score(100){};
    void give(string name1, int age1, double score1);
};

void Student::give(string name1, int age1, double score1)
{   
    this->name=name1;
    this->age=age1;
    this->score=score1;
};

bool cmp(Student a, Student b)
{
    if(a.score!=b.score) return a.score < b.score;
    else return a.name < b.name;
}

bool operator < (const Student& a, const Student& b){
    if(a.score!=b.score) return a.score < b.score;
    else return a.name < b.name;
}

int main()
{
    int n;
    string temp1; int temp2; double temp3;
    Student mylist[1000];
    while(cin>>n){
        for (int i =0; i<n; i++)
        {
            cin>>temp1>>temp2>>temp3;
            mylist[i].give(temp1,temp2,temp3);
        }
        sort(mylist,mylist+n);
        for(int i=0; i<n; i++)
            cout<<mylist[i].name<<" "<<mylist[i].age<<" "<<mylist[i].score<<endl;
    }
}