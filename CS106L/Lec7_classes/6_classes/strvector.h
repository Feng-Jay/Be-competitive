//in case mutliple files in a project include strvector, 
//this instruction says only compile this file once!
#ifndef STRVECTOR_H
#define STRVECTOR_H

#include <string>


class StrVector {
    public:
        //type alias (this is how iterator types work!)
        using iterator = std::string*;
        void insert(iterator pos, std::string to_add);
        //define an initial size for your underlying array
        const size_t kInitialSize = 2;
        
        //constructors and destructor
        iterator begin();
        iterator end();
        size_t size();
        StrVector();
        StrVector(size_t n, const std::string & inits);
        // StrVector(int)
        ~StrVector();
        
    private:
        void grow();
        std::string* elem;
        size_t allocated_size;
        size_t logical_size;
};

#endif // STRVECTOR_H


