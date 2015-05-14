/*
 * eytzinger_array.h
 *
 *  Created on: 2015-04-24
 *      Author: morin
 */

#ifndef FBS_EYTZINGER_ARRAY_H_
#define FBS_EYTZINGER_ARRAY_H_

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <cassert>

#include "base_array.h"

using std::cout;
using std::endl;

namespace fbs {

template<typename T, typename I>
class eytzinger_array : public base_array<T,I> {
protected:
	using base_array<T,I>::a;
	using base_array<T,I>::n;

	template<typename ForwardIterator>
	ForwardIterator copy_data(ForwardIterator a0, I i);

public:
	eytzinger_array() { };

	template<typename ForwardIterator>
	eytzinger_array(ForwardIterator a0, I n0);

	~eytzinger_array();

	I search(const T &x);
};

template<typename T, typename I>
template<typename ForwardIterator>
ForwardIterator eytzinger_array<T,I>::copy_data(ForwardIterator a0, I i) {

	if (i >= n) return a0;

	// visit left child
	a0 = copy_data(a0, 2*i+1);

	// put data at the root
	a[i] = *a0++;

	// visit right child
	a0 = copy_data(a0, 2*i+2);

	return a0;
}


template<typename T, typename I>
template<typename ForwardIterator>
eytzinger_array<T,I>::eytzinger_array(ForwardIterator a0, I n0) {
	if (n0 > std::numeric_limits<I>::max()/2) {
		std::ostringstream ss;
		ss << "array length " << n0 << " is too big, use a larger I class";
		throw std::out_of_range(ss.str());
	}
	n = n0;
	a = new T[n];
	copy_data(a0, 0);
}

template<typename T, typename I>
eytzinger_array<T,I>::~eytzinger_array() {
	delete[] a;
}

template<typename T, typename I>
I __attribute__ ((noinline)) eytzinger_array<T,I>::search(const T &x) {
	I j = n;
	I i = 0;
	while (i < n) {
		if (x < a[i]) {
			j = i;
			i = 2*i + 1;
		} else if (x > a[i]) {
			i = 2*i + 2;
		} else {
			return i;
		}
	}
	return j;
}


template<typename T, typename I>
class eytzingerpf_array : public eytzinger_array<T,I> {
protected:
	using eytzinger_array<T,I>::a;
	using eytzinger_array<T,I>::n;
	I mask;

public:
	template<typename ForwardIterator>
	eytzingerpf_array(ForwardIterator a0, I n0)
		: eytzinger_array<T,I>(a0, n0) {
		for (mask = 1; 2*mask < n; mask <<= 1);
		mask -= 1;
//		cout << mask << endl;
	} ;
	I search(const T &x);
};

template<typename T, typename I>
I __attribute__ ((noinline)) eytzingerpf_array<T,I>::search(const T &x) {
	I j = n;
	I i = 0;
	while (i < n) {
		__builtin_prefetch(a+16*i + 23, 0, 0);
		const T current = a[i];
		I left = 2*i + 1;
		I right = 2*i + 2;
		j = (x <= current) ? i : j;
		i = (x <= current) ? left : right;
	}

	return j;
}


template<typename T, typename I>
class eytzingerpfa_array : public eytzinger_array<T,I> {
protected:
	using eytzinger_array<T,I>::a;
	using eytzinger_array<T,I>::n;
	using eytzinger_array<T,I>::copy_data;

public:
	template<typename ForwardIterator>
	eytzingerpfa_array(ForwardIterator a0, I n0)
		: eytzinger_array<T,I>() {
			n = n0;
			// a = new T[n+1];
			assert(posix_memalign((void **)&a, 64, sizeof(T) * (n+1)) == 0);
			a++;
			copy_data(a0, 0);
			//std::size_t space = sizeof(T)*(n+1);
			//std::align(64, sizeof(T)*n, &a, &space);
		} ;
	I search(const T &x);
	~eytzingerpfa_array() { a--; free(a); a = new T[1]; }
};

template<typename T, typename I>
I __attribute__ ((noinline)) eytzingerpfa_array<T,I>::search(const T &x) {
	I j = n;
	I i = 0;
	while (i < n) {
		__builtin_prefetch(a+16*i + 15, 0, 0);
		const T current = a[i];
		I left = 2*i + 1;
		I right = 2*i + 2;
		j = (x <= current) ? i : j;
		i = (x <= current) ? left : right;
	}

	return j;
}


} // namespace fbs

#endif /* FBS_EYTZINGER_ARRAY_H_ */
