/*
 * eytzinger_array.h
 *
 *  Created on: 2015-04-24
 *      Author: morin
 */

#ifndef FBS_EYTZINGER_ARRAY_H_
#define FBS_EYTZINGER_ARRAY_H_

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "base_array.h"

namespace fbs {

template<typename T, typename I, bool early_termination = false>
class eytzinger_array : public base_array<T,I> {
protected:
	using base_array<T,I>::a;
	using base_array<T,I>::n;

	template<typename ForwardIterator>
	ForwardIterator copy_data(ForwardIterator a0, I i);

public:
	template<typename ForwardIterator>
	eytzinger_array(ForwardIterator a0, I n0);
	~eytzinger_array();
	I search(const T x);
};

template<typename T, typename I, bool e>
template<typename ForwardIterator>
ForwardIterator eytzinger_array<T,I,e>::copy_data(ForwardIterator a0, I i) {

	if (i >= n) return a0;

	// visit left child
	a0 = copy_data(a0, 2*i+1);

	// put data at the root
	a[i] = *a0++;

	// visit right child
	a0 = copy_data(a0, 2*i+2);

	return a0;
}


template<typename T, typename I, bool e>
template<typename ForwardIterator>
eytzinger_array<T,I,e>::eytzinger_array(ForwardIterator a0, I n0) {
	if (n0 > std::numeric_limits<I>::max()/2) {
		std::ostringstream ss;
		ss << "array length " << n0 << " is too big, use a larger I class";
		throw std::out_of_range(ss.str());
	}
	n = n0;
        int r = posix_memalign((void **)&a, 1UL << 21, sizeof(T) * n);
        assert(r == 0);
	copy_data(a0, 0);
}

template<typename T, typename I, bool e>
eytzinger_array<T,I,e>::~eytzinger_array() {
	free(a);
}

template<typename T, typename I, bool early_termination>
__attribute__((noinline))
I eytzinger_array<T,I,early_termination>::search(const T x) {
	I j = n;
	I i = 0;
        while (i < n) {
                const T current = a[i];
                I left = 2 * i + 1;
                I right = 2 * i + 2;

                if (early_termination && current == x) {
                        return i;
                }

                j = (x <= current) ? i : j;
                i = (x <= current) ? left : right;
	}

	return j;
}

} // namespace fbs


#endif /* FBS_EYTZINGER_ARRAY_H_ */
