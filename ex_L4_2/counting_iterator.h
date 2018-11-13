#ifndef COUNTING_ITERATOR_H_
#define COUNTING_ITERATOR_H_

template<typename T>
class counting_iterator :
	public std::iterator<std::bidirectional_iterator_tag, T>
{

	T t;

public:

	counting_iterator(T t = 0) : t(t)
	{
		/* void */
	}

	counting_iterator& operator ++()
	{
		++t;
		return *this;
	}

	counting_iterator& operator --()
	{
		--t;
		return *this;
	}

	counting_iterator operator ++(int)
	{
		counting_iterator i = *this;
		++(*this);
		return i;
	}

	counting_iterator operator --(int)
	{
		counting_iterator i = *this;
		--(*this);
		return i;
	}

	bool operator ==(counting_iterator other) const
	{
		return t == other.t;
	}

	bool operator !=(counting_iterator other) const
	{
		return !(*this == other);
	}

	T operator *() const {
		return t;
	}

};

template<typename T>
counting_iterator<T> counter(const T& t)
{
	return counting_iterator<T>(t);
}

#endif  // COUNTING_ITERATOR_H_
