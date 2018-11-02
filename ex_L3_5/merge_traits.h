#ifndef MERGE_TRAITS_H_
#define MERGE_TRAITS_H_

#include <list>
#include <vector>

template<typename T, typename E>
struct merge_traits
{

	static void merge(T& t, const E e)
	{
		t.insert(e);
	}

};

template<typename E>
struct merge_traits<std::vector<E>, E>
{

	static void merge(std::vector<E>& v, const E e)
	{
		v.push_back(e);
	}

};

template<typename E>
struct merge_traits<std::list<E>, E>
{

	static void merge(std::list<E>& v, const E e)
	{
		v.push_back(e);
	}

};

#endif  // MERGE_TRAITS_H_
