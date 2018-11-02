#ifndef MERGER_H_
#define MERGER_H_

#include "merge_traits.h"

namespace merger {

template<typename E, typename C1, typename C2, typename M=merge_traits<C1, E>>
void merge(C1& a, const C2& b) {
	for (E e : b) {
		M::merge(a, e);
	}
}

}

#endif  // MERGER_H_
