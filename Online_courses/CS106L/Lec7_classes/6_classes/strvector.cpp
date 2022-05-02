//dont forget to include the .h file!
//implementation for strvector.cpp goes here!

#include "strvector.h"
#include <iostream>

StrVector::StrVector()
	:allocated_size(0),
	 logical_size(kInitialSize)
{
	elem = new std::string [kInitialSize];
	for(StrVector::iterator i = begin(); i!=end(); ++i){
		*i = "init";
	}

}

StrVector::StrVector(size_t n, const std::string & inits)
	:allocated_size(n*2),
	 logical_size(n)
{
	elem = new std::string [allocated_size];
	for(StrVector::iterator i = begin(); i!=end(); ++i){
		*i = inits;
	}
}

StrVector::iterator StrVector::begin(){
	return elem;
}

StrVector::iterator StrVector:: end(){
	return elem+allocated_size;
}

size_t StrVector::size(){
	return allocated_size;
}

StrVector:: ~StrVector(){
	delete [] elem;
	std::cout << "Destoried"<<std::endl;
}

void StrVector::grow(){
	std::string* temp = new std::string [size()*2];
	std:: copy(begin(), end(), temp);
	delete [] elem;
	logical_size = size()*2;
	elem = temp;
}

void StrVector::insert(StrVector::iterator pos, std::string to_add){
	size_t index = pos - begin();
	if (pos > end()){
		std::cout<<"Invalid pos!"<<std::endl;
		return ;
	}
	if (size() == logical_size){
		grow();
	}
	pos = begin()+index;
	std:: copy_backward(pos, end(), end()+1);
	*pos = to_add;
	++allocated_size;
}


