/*
 * mixed_array.h
 *
 *  Created on: 2015-05-26
 *      Author: morin
 */
#ifndef FBS_MIXED_ARRAY_H_
#define FBS_MIXED_ARRAY_H_

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <cassert>
#include <cstdint>


#include "base_array.h"

namespace fbs {

// An array that starts with a full Eytzinger tree containing roughly n/(B+1)
// elements followed by the remaining elements in sorted order.  Elements are
// chosen so that a search in the Eytzinger tree leads to a block of B elements
template<typename T, typename I, unsigned W=64>
class mixed_array : public base_array<T,I> {
protected:
	using base_array<T,I>::a;
	using base_array<T,I>::n;

	// The size of the complete Eytzinger tree part
	I m;

	// The height of the complete Eytzinger subtree
	I h;

	// We always prefetch multiplier*i + offset
	static const I B = W/sizeof(T);
	static const I multiplier = B;
	static const I offset = multiplier-1;

	template<typename ForwardIterator>
	void copy_data(ForwardIterator a0);

	template<typename ForwardIterator>
	ForwardIterator copy_data_r(ForwardIterator a0, I i);

	template<unsigned int C>
	static const T* branchfree_inner_search(const T *base, const T x) {
		if (C <= 1) return base;
		const unsigned int half = C / 2;
		const T *current = &base[half];
		return branchfree_inner_search<C - half>((*current < x) ? current : base, x);
	}

	template<bool prefetch=false>
	I _search(T x) const;

	I prefetch_search(T x) const { return _search<true>(x); };

public:
	template<typename ForwardIterator>
	mixed_array(ForwardIterator a0, I n0);

	~mixed_array();

	I search(T x) const { return _search(x); };
};

template<typename T, typename I, unsigned W=64>
class mixed_array_pf : public mixed_array<T,I,W> {
protected:

	using mixed_array<T,I,W>::prefetch_search;

public:

	template<typename ForwardIterator>
	mixed_array_pf(ForwardIterator a0, I n0) : mixed_array<T,I,W>(a0, n0) {};

	I search(T x) const { return prefetch_search(x); };
};


template<typename T, typename I, unsigned W>
template<typename ForwardIterator>
ForwardIterator mixed_array<T,I,W>::copy_data_r(ForwardIterator a0, I i) {

	if (i >= m) return a0;

	// visit left child
	a0 = copy_data_r(a0, 2*i+1);

	// put data at the root
	a[i] = *a0++;

	// visit right child
	a0 = copy_data_r(a0, 2*i+2);

	return a0;
}

template<typename T, typename I, unsigned W>
template<typename ForwardIterator>
mixed_array<T,I,W>::mixed_array(ForwardIterator a0, I n0) {
	n = n0;

	// FIXME: Use std::align once gcc supports it
	assert(posix_memalign((void **)&a, 64, sizeof(T) * (n+1)) == 0);
	a++;
	std::fill_n(a, n, 0);   // FIXME: for debugging only

	// Figure out the height and size of the complete Eytzinger part
	h = 0;
	while (((1<<(h+1))-1) + B*(1<<(h+1)) < n) h++;
	m = (1<<(h+1))-1;

	// Figure out how much is at the leaves
	I q = (n - m)/B; // the number of full leaves
	I r = (n - m)%B; // number of items in the last partial leaf

	// Now build everything
	T *atmp = new T[m];   // keep the Eytzinger data in here
	for (int i = 0; i < q; i++) {
		atmp[i] = a0[B+(B+1)*i];
		std::copy_n(a0+(B+1)*i, B, a+m+B*i);
	}
	std::copy_n(a0+(B+1)*q+r, m-q, atmp+q);
	std::copy_n(a0+(B+1)*q, r, a+m+B*q);
	copy_data_r(atmp, 0); // make the Eytzinger part
	delete[] atmp;
}

template<typename T, typename I, unsigned W>
mixed_array<T,I,W>::~mixed_array() {
	free(a-1);
}

// Branch-free code without or without prefetching
template<typename T, typename I, unsigned W>
template<bool prefetch>
I __attribute__ ((noinline)) mixed_array<T,I,W>::_search(T x) const {
	// Search in the (complete) Eytzinger tree
	I i = 0;
	for (I d = 0; d <= h; d++) {
		if (prefetch) __builtin_prefetch(a+(multiplier*i + offset));
		i = (x <= a[i]) ? (2*i + 1) : (2*i + 2);
	}
	I j = (i+1) >> __builtin_ffs(~(i+1));
	j = (j == 0) ? n : j-1;

	// Make i point to the first element of a block
	i = m + (i-m)*B;

	if (i < n) {
		// do branch-free binary search on the block
		const T *base = &a[i];
		I b = std::min(n - i, B);
		const I c = b;
		while (b > 1) {
			I half = b / 2;
			const T *current = &base[half];
			base = (*current < x) ? current : base;
			b -= half;
		}
		I nth = (*base < x) + base - &a[i];
		j = (nth < c) ? nth+i : j;
	}

// The following code was tested and found to be significantly slower
// if (__builtin_expect(i + B <= n, 1)) {
//		// searching a full block - use unrolled branch-free binary search
//		const T *base = &a[i];
//		const T *pred = branchfree_inner_search<B>(base, x);
//		I nth = (*pred < x) + pred - base;
//		j = (nth == B) ? j : i + nth;
//	} else if (__builtin_expect(i < n, 0)) {
//		// searching a partial block - use branch-free binary search
//		const T *base = &a[i];
//		I b = n - i;
//		while (b > 1) {
//			I half = b / 2;
//			const T *current = &base[half];
//			base = (*current < x) ? current : base;
//			b -= half;
//		}
//		I ret = (*base < x) + base - a;
//		j = (ret < n) ? ret : j;
//	}
	return j;
}

} // namespace fbs

#endif /* FBS_MIXED_ARRAY_H_ */
