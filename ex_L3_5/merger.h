#ifndef MERGER_H_
#define MERGER_H_

#include "merge_traits.h"

template<typename C1, typename C2, typename E, typename M=merge_traits<C1, E>>
class merger
{

public:

	merger() = default;

	void operator ()(C1& a, C2& b) {
		for (auto e : b) {
			M::merge(a, e);
		}
	}

};

#endif  // MERGER_H_
