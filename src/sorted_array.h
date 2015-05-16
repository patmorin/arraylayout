/*
 * sorted_array.h
 *
 *  Created on: 2015-04-24
 *      Author: morin
 */

#ifndef FBS_SORTED_ARRAY_H_
#define FBS_SORTED_ARRAY_H_

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "base_array.h"

namespace fbs {

template<typename T, typename I>
class sorted_array : public base_array<T,I> {
protected:
	using base_array<T,I>::a;
	using base_array<T,I>::n;

	template<bool prefetch>
	I _branchfree_search(T x) const;

public:
	template<typename ForwardIterator>
	sorted_array(ForwardIterator a0, I n0);
	~sorted_array();
	I branchy_search(T x) const;
	I branchfree_search(T x) const { return _branchfree_search<false>(x); };
	I branchfree_prefetch_search(T x) const { return _branchfree_search<true>(x); };
	I search(T x) const { return branchy_search(x); };
};

template<typename T, typename I>
class sorted_array_bf : public sorted_array<T,I> {
	using sorted_array<T,I>::branchfree_search;
public:
	template<typename ForwardIterator>
	sorted_array_bf(ForwardIterator a0, I n0) : sorted_array<T,I>(a0, n0) { };

	I search(T x) const { return branchfree_search(x); };
};

template<typename T, typename I>
class sorted_array_bfp : public sorted_array<T,I> {
	using sorted_array<T,I>::branchfree_prefetch_search;
public:
	template<typename ForwardIterator>
	sorted_array_bfp(ForwardIterator a0, I n0) : sorted_array<T,I>(a0, n0) { };

	I search(T x) const { return branchfree_prefetch_search(x); };
};

template<typename T, typename I>
template<typename ForwardIterator>
sorted_array<T,I>::sorted_array(ForwardIterator a0, I n0) {
		n = n0;
		a = new T[n];
		std::copy_n(a0, n, a);
}

template<typename T, typename I>
sorted_array<T,I>::~sorted_array() {
	delete[] a;
}

template<typename T, typename I>
I __attribute__ ((noinline)) sorted_array<T,I>::branchy_search(T x) const {
	const T t = x;
	const T *a = this->a;
	I lo = 0;
	I hi = n;
	while (lo < hi) {
		I m = (lo + hi) / 2;
		if (t < a[m]) {
			hi = m;
		} else if (t > a[m]) {
			lo = m+1;
		} else {
			return m;
		}
	}
	return hi;
}


template<typename T, typename I>
template<bool prefetch>
I __attribute__ ((noinline)) sorted_array<T,I>::_branchfree_search(T x) const {
	const T *base = a;
	I n = this->n;
	while (n > 1) {
		I half = n / 2;
		if (prefetch) {
			__builtin_prefetch(base + half/2, 0, 0);
			__builtin_prefetch(base + half + half/2, 0, 0);
		}
		const T *ptr = &base[half];
		const T current = *ptr;
		base = (current < x) ? ptr : base;
		n -= half;
	}
	return (*base < x) + base - a;
}

} // namespace fbs

#endif /* FBS_SORTED_ARRAY_H_ */
