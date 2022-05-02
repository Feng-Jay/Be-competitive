
//What do we need to include?
#include <iostream>
#include <string>
#include <fstream>

//No using namespace std;!!!!
using std::cout;
using std::endl;
using std::string;

//function to write num to any ostream
void wtite2anyostream(std::ostream &want_ostream, int num)
{
    want_ostream << "In the integrated function, The answer is: "<< num <<endl;
}

int main() {
    // Write an int to the user's console.
    int myNum = 42;
    cout << "The answer is: " << myNum << endl;

    // Write an int to a file.
    std::ofstream out_stream("out.txt");

    out_stream << "The answer is: " << myNum << endl;
    
    std::ofstream fileOut("out.txt");
    // Write method to take any ostream
    wtite2anyostream(cout, myNum+1);
    wtite2anyostream(fileOut, myNum+1);
    // write over method.
    
   
    return 0;
}
