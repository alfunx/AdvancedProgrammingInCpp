#ifndef DUMB_POINTER_H_
#define DUMB_POINTER_H_

#include <iostream>

template<typename T>
class dumb_pointer
{

	T* data;

	friend std::ostream& operator <<(std::ostream& os, dumb_pointer<T>& p)
	{
		os << '(' << "address: " << (void*)p.data << ')';
		return os;
	}

public:

	dumb_pointer(T* t) : data(t)
	{
		/* void */
	}

	~dumb_pointer()
	{
		delete data;
	}

	T& operator *()
	{
		return *data;
	}

	T* operator ->()
	{
		return data;
	}

};

#endif  // DUMB_POINTER_H_
