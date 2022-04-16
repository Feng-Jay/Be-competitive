#include "queue.h"

struct Customer{
    int windows;
    int time;
};

int best(Queue<Customer>* windows, int nwin)
{
    int min = 0;
    for(int i=1; i <nwin; ++i){
        if(windows[min].size() > windows[i].size())
            min = i;
    }
    return min;

}

void simulator(int nwin, int servtime)
{
    Queue<Customer>* windows = new Queue<Customer> [nwin];
    // each window has a queue
    for(int now=0; now < servtime; ++now){
        if(std::rand()%(1+nwin)){
            Customer c;
            c.time = 1+ std::rand()%98;
            c.windows = best(windows, nwin);
            windows[c.windows].enqueue(c);
            std::cout<<"customer c in "<<c.windows<<" "<<c.time<<"s\n";
        }
        for(int i=0;i<nwin;++i){
            if(!windows[i].empty()){
                if(--windows[i].front().time <=0)
                    {
                        std::cout<<"customer out "<< windows[i].front().windows<<std::endl;
                        windows[i].dequeue();
                    }
            }
        }
    }
    delete [] windows;
}

int main()
{
    simulator(10, 10000);
}