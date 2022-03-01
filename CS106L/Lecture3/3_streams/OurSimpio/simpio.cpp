#include <iostream>
#include <sstream>

using std::cout;    using std::endl;
using std::cin;     using std::string;


string IntegerToString(int myInt) {

    std::ostringstream formatter;
    /*
     * We'll specifically use an ostringstream, which is just a
     * stringstream that you can only put things into.
     */
    formatter << myInt <<endl;
    /*
     * Putting the int into the ostringstream will convert
     * it into a string format.
     */

     /* Ask for the string inside the ostringstream. */
     return formatter.str();
}

int StringToInteger(const string& str) {
   std:: istringstream formatter(str);
    /*
     * We'll specifically use an istringstream, which is just a
     * stringstream that you can only get things from.
     *
     * You can set its internal string when creating it or by doing
     * converter.str("string_to_set");
     */

   int temp;
   if(formatter >> temp){
    /*
     * Try getting an int from the stream. If this is not succesful
     * then user input was not a valid input.
     */
      char temp2;
      if (formatter >> temp2){
      /*
         * See if we can extract a char from the stream.
         * If so, the user had junk after a valid int in their input.
         */
            throw std:: domain_error(string("Unexpected input!!!: ")+temp2); 
            /*
             * Throwing an error is a way of propogating up the funcion
             * callstack that something went wrong. Previous functions can
             * anticipate such an error and catch it. In this case, we will
             * just let the thrown domain_error propogate up until it terminates
             * the program.
             *
             * A domain_error is defined in the standard namespace as an error
             * to signal that the input arguments to the function were not valid.
             */
      }
      return  temp;
   }
    throw std::domain_error(string("Can not convert to integer: ")+str);
    /* If read unsuccessful, throw a domain error with a helpful error message. */
}

int getInteger() {
      while(true){
         string line;
         std::getline(cin, line);
        /* First we get a line of input from the user. */
        std::istringstream formatter(line);
        /*
         * We'll  use an istringstream because we only want to pull data
         * out of the stream once we have put the string's contents in it.
         */
        int result;
        if(formatter >> result){
        /*
         * Try getting an int from the stream. If this is not succesful
         * then user input was not a valid input.
         */
            char temp;
            if(formatter >> temp){
               cout << "Unexpected character!!!"<<endl;
            /*
             * See if we can extract a char from the stream.
             * If so, the user had junk after a valid int in their input.
             */
            }else {
               return  result;
            /*
             * Input was succesfully converted to int with no
             * trailing stuff at the end.
             */
            }
        }else {
         cout << "Not valid, AGAIN!!!"<<endl;
        }
      }   
}

int main() {
   int x = getInteger();
   cout << "We got: " << x << endl;
   // string outcome = IntegerToString(111);
   // cout << outcome << endl;
   string out1 = IntegerToString(x);
   cout<<"string is "<<out1 <<endl;
   int out2 = StringToInteger(out1);
   cout<<"int is " <<out2 <<endl;
   return 0;
}
