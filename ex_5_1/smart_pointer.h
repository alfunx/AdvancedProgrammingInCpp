#ifndef SMART_POINTER_H_
#define SMART_POINTER_H_

#include <iostream>

template<typename T>
class smart_pointer
{

	T* data;
	int* count;

	inline void acquire()
	{
		++(*count);
	}

	inline void release()
	{
		if (--(*count) <= 0) {
			delete data;
			delete count;
		}
	}

	friend std::ostream& operator <<(std::ostream& os, smart_pointer<T>& p)
	{
		os << '(' << "address: " << (void*)p.data << ", "
			<< "count: " << *p.count << ')';
		return os;
	}

public:

	smart_pointer(T* t) : data(t)
	{
		count = new int(1);
	}

	smart_pointer(const smart_pointer<T>& p) : data(p.data), count(p.count)
	{
		acquire();
	}

	~smart_pointer()
	{
		release();
	}

	T& operator *()
	{
		return *data;
	}

	T* operator ->()
	{
		return data;
	}

	smart_pointer<T>& operator =(const smart_pointer<T>& p)
	{
		if (this == &p)
			return *this;

		release();
		data = p.data;
		count = p.count;
		acquire();

		return *this;
	}

};

#endif  // SMART_POINTER_H_
