// system and timing
#include <iostream>
#include <chrono>

// data structure imports
#include <deque>
#include <vector>
#include <iterator>
#include <utility> // pair

using std::cout;    using std::endl;

// count_occurrences
template <class mainstr, class pattern>
auto count_occurrences(mainstr begin, mainstr end, pattern pat)
{
    int count = 0;
    for (auto i = begin; i!= end; ++i){
        if(*i == pat) ++count;
    }
    return count;
}

int main() {

    // vector of strings
    std::vector<std::string> lands = {"Xadia", "Drakewood", "Innean"};
    // how can we count the number of times "Xadia" appears in this?
    cout << count_occurrences(lands.begin(), lands.end(), "Xadia");
    cout << endl;
    // string itself (array of chars)
    std::string str = "Xadia";
    // how can we count the number of times 'a' appears in this?
    cout << count_occurrences(str.begin(), str.end(), 'a')<<endl;
    return 0;
}

