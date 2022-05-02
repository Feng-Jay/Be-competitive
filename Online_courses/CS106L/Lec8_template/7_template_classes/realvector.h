#ifndef RealVector_H
#define RealVector_H

#include <string>

template <class type> 
class RealVector{
	public: 
		const size_t Initialsize = 2;
		RealVector();
		RealVector(size_t n, const type & inits);
		~RealVector();
		using iterator = type *;
		iterator begin();
		iterator end();
		size_t size() const;
		using const_iterator = const type *;
		const_iterator cbegin() const;
		const_iterator cend() const;
		void insert(size_t pos, const type & add);
		void push_back(const type & pub);
	private:
		type* elems;
		size_t logical_size;
		size_t used_size;
		void grow();
};

#include "realvector.cpp"

#endif
