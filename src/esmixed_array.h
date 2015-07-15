/*
 * esmixed_array.h
 *
 *  Created on: 2015-05-26
 *      Author: morin
 */

#ifndef FBS_ESMIXED_ARRAY_H_
#define FBS_ESMIXED_ARRAY_H_

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <cassert>
#include <cstdint>


#include "base_array.h"

namespace fbs {

// An array that has an esmixed layout of a 1/(B+1) sample followed by the
// remaining data in sorted order
template<typename T, typename I, unsigned W=64>
class esmixed_array : public base_array<T,I> {
protected:
	using base_array<T,I>::a;
	using base_array<T,I>::n;

	// The size of the Eytzinger tree part
	I m;

	// The height of the _complete_ Eytzinger subtree
	I h;

	// The number of leaves in the (partial) bottom level
	I bottom_level;

	// We always prefetch multiplier*i + offset
	static const I B = W/sizeof(T);
	static const I multiplier = B;
	static const I offset = multiplier-1;

	template<typename ForwardIterator>
	void copy_data(ForwardIterator a0);

	template<typename ForwardIterator>
	ForwardIterator copy_data_r(ForwardIterator a0, I i);

	template<unsigned int Q>
	const T* inner_search(const T *base, const T x) const {
		if (Q <= 1) return base;
		const unsigned int half = Q / 2;
		const T *current = &base[half];
		return inner_search<Q - half>((*current < x) ? current : base, x);
	}

public:
	template<typename ForwardIterator>
	esmixed_array(ForwardIterator a0, I n0);

	~esmixed_array();

	I search(T x) const;
};

template<typename T, typename I, unsigned W>
template<typename ForwardIterator>
ForwardIterator esmixed_array<T,I,W>::copy_data_r(ForwardIterator a0, I i) {

	if (i >= m) return a0;

	// visit left child
	a0 = copy_data_r(a0, 2*i+1);

	// put data at the root
	a[i] = *a0;
//	cout << "a[" << i << "]=" << *a0 << endl;
	a0 += B+1;

	// visit right child
	a0 = copy_data_r(a0, 2*i+2);

	return a0;
}

template<typename T, typename I, unsigned W>
template<typename ForwardIterator>
esmixed_array<T,I,W>::esmixed_array(ForwardIterator a0, I n0) {
	n = n0;
//	cout << "multiplier = " << multiplier << ", offset = " << offset << endl;
	// FIXME: Use std::align once gcc supports it
	assert(posix_memalign((void **)&a, 64, sizeof(T) * (n+1)) == 0);
	a++;

	// The size of our Eytzinger tree.
	m = n/(B+1);

	for (h = 0; (1 << (h+1))-1 < m; h++);
	h--;
	bottom_level = m - ((1 << (h+1))-1);
//	cout << "m = " << m << ", h = " << h
//			<< ", bottom_level = " << bottom_level << endl;

	// Build the top part using a[B+i(B+1)] for i in 0,...,m-1
	copy_data_r(a0+B, 0);

	// Build remainder using everything else
	for (int i = 0; i < m; i++) {
		std::copy_n(a0+(B+1)*i, B, a+m+B*i);
	}
	std::copy_n(a0+(B+1)*m, n-(B+1)*m, a+m+B*m);

//	for (int i = 0; i < n; i++) {
//		cout << a[i] << ",";
//	}
//	cout << endl;
}

template<typename T, typename I, unsigned W>
esmixed_array<T,I,W>::~esmixed_array() {
	a--;
	free(a);
}

// Branch-free code without or without prefetching
template<typename T, typename I, unsigned W>
I __attribute__ ((noinline)) esmixed_array<T,I,W>::search(T x) const {
	// Search the Eytzinger tree
//	cout << "Searching for " << x << endl;
	I i = 0;
	I j = n;
	I p = 0;
	for (I d = 0; d <= h; d++) {
		__builtin_prefetch(a+(multiplier*i + offset));
		const T current = a[i];
		I left = 2*i + 1;
		I right = 2*i + 2;
		p = (p << 1) | (x > current);
		j = (x <= current) ? i : j;
		i = (x <= current) ? left : right;
	}
	const I ip = i;
	i = (ip < m) ? i : (i-1)/2;
	const T current = a[i];
	p = (ip < m) ? (p << 1) | (x > current) : p;
	j = (x <= current) ? i : j;
	p = (ip >= m) ? p + bottom_level : p;

//	The preceding code is a branch-free implementation of this:
//	if (i < m) {
//		const T current = a[i];
//		p = (p << 1) | (x > current);
//		j = (x <= current) ? i : j;
//	} else {
//		p += bottom_level;
//	}

//	cout << "Current best is " << a[j] << endl;
	const I lo = m+p*B;
	const T *base = a + lo;

//	I hi = std::min(n, lo+B)-1;
//	cout << "Searching in " << a[lo] << ",...," << a[hi] << endl;

	if (__builtin_expect(lo + B < n, 1)) {
		// The usual case - searching a block of size B
		const T *pred = inner_search<B>(base, x);
		I jp = (*pred < x) + pred - base;
		j = (jp < B) ? lo + jp : j;
//		cout << "Full block search returns " << a[j] << endl;
	} else {
		// searching partial block
		I m = n - lo;
		while (m > 1) {
			I half = m / 2;
			const T *current = &base[half];
			base = (*current < x) ? current : base;
			m -= half;
		}
		I ret = (*base < x) + base - a;
		j = (ret == n) ? j : ret;
//		cout << "Partial block search returns " << a[j] << endl;
	}
	return j;

	// Now start binary search
//	I lo = m + p*n/m;      // FIXME: Real danger of overflow
//	I hi = m + (p+1)*n/m;  // FIXME: Real danger of overflow
//	const T *base = &a[lo];
//	I n = hi-lo;
//	while (n > 1) {
//		I half = n / 2;
//		const T *ptr = &base[half];
//		const T current = *ptr;
//		base = (current < x) ? ptr : base;
//		n -= half;
//	}
//	return (*base < x) + base - a;
}

} // namespace fbs

#endif /* FBS_ESMIXED_ARRAY_H_ */
