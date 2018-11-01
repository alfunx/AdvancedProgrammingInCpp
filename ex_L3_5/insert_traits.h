#ifndef INSERT_TRAITS_H_
#define INSERT_TRAITS_H_

#include <list>
#include <vector>

template<typename T, typename E>
struct insert_traits
{

	static void insert(T& t, E e)
	{
		t.insert(e);
	}

};

template<typename E>
struct insert_traits<std::vector<E>, E>
{

	static void insert(std::vector<E>& v, E e)
	{
		v.push_back(e);
	}

};

template<typename E>
struct insert_traits<std::list<E>, E>
{

	static void insert(std::list<E>& v, E e)
	{
		v.push_back(e);
	}

};

#endif  // INSERT_TRAITS_H_
