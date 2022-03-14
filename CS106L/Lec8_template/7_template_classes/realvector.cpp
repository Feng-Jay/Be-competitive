#include "realvector.h"

template <class type>
RealVector<type>:: RealVector()
:logical_size(RealVector<type>::Initialsize),
 used_size(0)
{
	elems = new type [Initialsize];
}

template <class type>
RealVector<type>::RealVector(size_t n, const type & inits)
	:logical_size(n),
	  used_size(n)
{
	elems = new type [logical_size];
	for (size_t i =0; i <n; ++i){
		elems[i] = inits;
	}
}

template <class type> 
RealVector<type>:: ~RealVector(){
	delete [] elems;
}

template <class type>
typename RealVector<type>::const_iterator RealVector<type>::cbegin() const{
	return elems;
}

template <class type>
typename RealVector<type>:: const_iterator RealVector<type>:: cend() const{
	return elems+size();
}

template <class type>
size_t RealVector<type>::size() const{
	return used_size;
}

template <class type>
void RealVector<type>::grow(){
	type * temp = new type [logical_size*2];
	std::copy(cbegin(), cend(), temp);
	delete [] elems;
	elems = temp;
	logical_size *= 2;
	return;
}

template <class type> 
typename RealVector<type>::iterator RealVector<type>::begin(){
	return elems;
}

template <class type> 
typename RealVector<type>::iterator RealVector<type>::end(){
	return elems+size();
}

template <class type>
void RealVector<type>:: insert(size_t pos, const type &add){
	// size_t index = pos - begin();
	if (used_size == logical_size){
		grow();
	}
	std::copy(begin()+pos, end(), begin()+pos+1);
	*(begin()+pos) = add;
	++used_size;
	return;
	// pos = index + begin();

}