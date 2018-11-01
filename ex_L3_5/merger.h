#ifndef MERGER_H_
#define MERGER_H_

#include "insert_traits.h"

template<typename T, typename E, typename I=insert_traits<T, E>>
class merger
{

public:

	merger() = default;

	void operator ()(T& a, T& b) {
		for (auto e : b) {
			I::insert(a, e);
		}
	}

};

#endif  // MERGER_H_
