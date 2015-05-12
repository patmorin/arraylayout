/*
 * btree_array.h
 *
 *  Created on: 2015-04-24
 *      Author: morin
 */

#ifndef FBS_BTREE_ARRAY_H_
#define FBS_BTREE_ARRAY_H_

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <limits>

#include "base_array.h"

using std::min;

namespace fbs {

/*
 * btree_array
 */
template<unsigned B, typename T, typename I, bool early_termination = false>
class btree_array : public base_array<T,I> {
protected:
	using base_array<T,I>::a;
	using base_array<T,I>::n;

	I child(unsigned c, I i) {
		return (B+1)*i + (c+1)*B;
	}

	template<class ForwardIterator>
	ForwardIterator copy_data(ForwardIterator a0, I i);

public:
	template<typename ForwardIterator>
	btree_array(ForwardIterator a0, I n0);

	~btree_array();

	I search(const T x);

};

template<unsigned B, typename T, typename I, bool e>
template<typename ForwardIterator>
ForwardIterator btree_array<B,T,I,e>::copy_data(ForwardIterator a0, I i) {
	if (i >= n) return a0;

	for (unsigned c = 0; c <= B; c++) {
		// visit c'th child
		a0 = copy_data(a0, child(c,i));
		if (c < B && i+c < n) {
			a[i+c] = *a0++;
		}
	}

	return a0;
}


template<unsigned B, typename T, typename I, bool e>
template<typename ForwardIterator>
btree_array<B,T,I,e>::btree_array(ForwardIterator a0, I n0) {
	if (n0-1 > std::numeric_limits<I>::max()/(B+1)-B) {
		std::ostringstream ss;
		ss << "array length " << n0 << " is too big, use a larger I class";
		throw std::out_of_range(ss.str());
	}
	n = n0;
	int r = posix_memalign((void **)&a, 1UL << 21, sizeof(T) * n);
	assert(r == 0);
	copy_data(a0, 0);
}

template<unsigned B, typename T, typename I, bool e>
btree_array<B,T,I,e>::~btree_array() {
	free(a);
}

template<unsigned int B, typename T>
static const T *inner_search(const T *base, const T x)
{
	if (B <= 1) {
		return base;
	}

	const unsigned int half = B / 2;
	const T *current = &base[half];
	return inner_search<B - half, T>((*current < x) ? current : base, x);
}

template<unsigned B, typename T, typename I, bool early_termination>
__attribute__((noinline))
I btree_array<B, T, I, early_termination>::search(const T x) {
	I j = n;
	I i = 0;
	while (i < n) {
		/* Last (partial block). */
		if (__builtin_expect(i + B >= n, 0)) {
			const T *base = &a[i];
			I m = n - i;

			while (m > 1) {
				I half = m / 2;
				const T *current = &base[half];

				base = (*current < x) ? current : base;
				m -= half;
			}

			I ret = (*base < x) + base - a;
			return (ret == n) ? j : ret;
		}

		const T *base = &a[i];
		const T *pred = inner_search<B, T>(base, x);
		unsigned int nth = (*pred < x) + pred - base;

		{
			/* nth == B iff x > all values in block. */
			const T current = base[nth % B];
			I next = i + nth;

			if (early_termination && current == x) {
				return next;
			}

			j = (current >= x) ? next : j;
		}

		i = child(nth, i);
	}
	return j;
}

} // namespace fbs


#endif /* FBS_BTREE_ARRAY_H_ */
