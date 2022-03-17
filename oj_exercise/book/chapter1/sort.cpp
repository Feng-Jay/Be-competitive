#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>
using std:: cin; using std:: cout;
using std:: endl; 

void swap(int *a,int *b) //交換兩個變數
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
// Bubble sort 
void bubble(int* list, int len)
{
    int* temp = list;
    for(int i= 0; i< len; ++i){
        for(int j=0; j< len-i-1; ++j){
            if(temp[j]>temp[j+1]){
                temp[j]= temp[j]^temp[j+1];
                temp[j+1]= temp[j]^temp[j+1];
                temp[j]= temp[j]^temp[j+1];
            }
        }
    }
}

// Select sort
void select(int* list, int len)
{
    for(int i= 0; i< len-1; ++i){
        int temp = i;
        for (int j= i+1; j< len; ++j){
            if(list[temp] > list[j]){
                temp = j;
            }
        }
        // cout<<temp<<endl;
        // list[i] = list[i]^list[temp];
        // list[temp]= list[i]^list[temp];
        // list[i] = list[i]^list[temp];
        swap(&list[i],&list[temp]);
    }
}

// Insert sort
void insert(int* list, int len)
{
    for(int i =1; i< len ;i++){
        int j = i-1;
        int temp = list[i];
        while((j>=0) && temp < list[j]){
            list[j+1] = list[j];
            j--;
        }
        list[j+1] = temp;
    }
}

//shell sort
void shell(int* list, int len)
{
    for(int gap = len>>1; gap>0; gap=gap>>1){
        for(int i= gap; i< len; ++i){
            int temp = list[i];
            int j = i;
            if(temp < list[j-gap]){
                while (j-gap>=0 && temp < list[j-gap])
                {
                    list[j] = list[j-gap];
                    j-=gap;
                }
                
            }
            list[j] = temp; 
        }
    }
}

//merge sort
void merge(int* list, int len)
{
    int* a= list;
    int* b= new int [len];
    for(int seg=1; seg<len; seg+=seg){
        for(int start = 0; start< len; start+=2*seg){
            int low= start; int mid= fmin(start+seg, len);
            int high = fmin(start+seg+seg, len);
            int start1 = low; int end1 = mid;
            int start2 = mid; int end2 = high;
            int k = low;
            while(start1<end1&&start2<end2)
                b[k++]= a[start1] < a[start2] ? a[start1++] : a[start2++];
            while(start1<end1)
                b[k++]=a[start1++];
            while(start2<end2)
                b[k++]=a[start2++];
        }
        int* temp = a;
        a = b;
        b = temp;
    }
    if (a != list) {
        int i;
        for (i = 0; i < len; i++)
            b[i] = a[i];
        b = a;
    }
    delete [] b;
}

int main(){
    int list[5] = {5,4,6,4,1};
    // bubble(list,5);
    // select(list,5);
    // insert(list,5);
    // shell(list,5);
    merge(list,5);
    for(int i=0; i<4;++i){
        cout<<list[i]<<" ";
    }
    cout<<list[4]<<endl;
    return 0; 
}