
#include <iostream>
#include <fstream>
#include <vector>

using std::cout;    using std::endl;
using std::string; using std::cin;

//read numbers from a file
void readNumbers() {
    std:: ifstream input("res/numbers.txt");
    // Create our ifstream and make it open the file
    int read;
    // Something to store values we get from the stream
    while(true){
        input >> read;
        // Extract next number from input
        if(input.fail() || input.eof()){
            break;
        }
        // If input is in a fail state, either a value couldn't
        // be converted, or we are at the end of the file.
        cout<< read << endl;
        //print whatever we read
    }
        
}

//read a single word at a time from a file
void readHaikuWord() {
    std::ifstream input("res/haiku.txt");
    // Create our ifstream and make it open the file
    string temp;
     // Something to store values we get from the stream
    while(true){
        input >> temp;
        // Extract next word from input
        if(input.fail() || input.eof()){
            break;
        }
        // If input is in a fail state, either a value couldn't
        // be converted, or we are at the end of the file.
        cout<<temp<<endl;
        //print whatever we read
    }
}

void readHaikuLine() {
    std::ifstream input("res/haiku.txt");
    // Create our ifstream and make it open the file
    string temp;
    // Something to store the lines as we get them form the stream
    while(true){
        std::getline(input, temp);
        if(input.fail() || input.eof()){
            break;
        }
        // If input is in a fail state, either a value couldn't
        // be converted, or we are at the end of the file.
        cout<<temp<<endl;
        //print whatever we read
    }
}



//function for us to play around with cin
void playground(){
    string line;
    std::ifstream in("res/haiku.txt");
    while(std::getline(in, line)){
        if(in.eof()){
        cout << "eof" << endl;
         // break;
        }
        else if (in.fail()) {
            cout << "fail" << endl;
            // break;
        }
        else cout << line << endl;
        cout << in.eof() << in.fail() << endl;
    }
    cout << in.eof() << in.fail() << endl;

}

int main() {

    // playground();
    cout<<"readNumbers"<<endl;
    readNumbers();
    cout<<"readHaikuWord"<<endl;
    readHaikuWord();
    cout<<"readHaikuLine"<<endl;
    readHaikuLine();

    return 0;
}


