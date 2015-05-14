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

public:
	template<typename ForwardIterator>
	sorted_array(ForwardIterator a0, I n0);
	~sorted_array();
	I search(T x);
};


template<typename T, typename I>
template<typename ForwardIterator>
sorted_array<T,I>::sorted_array(ForwardIterator a0, I n0)
{
		n = n0;
		a = new T[n];
		std::copy_n(a0, n, a);
}

template<typename T, typename I>
sorted_array<T,I>::~sorted_array() {
	delete[] a;
}

template<typename T, typename I>
I __attribute__ ((noinline)) sorted_array<T,I>::search(T x) {
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

} // namespace fbs

#endif /* FBS_SORTED_ARRAY_H_ */
