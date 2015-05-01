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

using std::cout;
using std::endl;

namespace fbs {

template<class T, class I>
class sorted_array : public base_array<T,I> {
protected:
	using base_array<T,I>::a;
	using base_array<T,I>::n;

public:
	sorted_array(T *a0, I n0);
	~sorted_array();
	I search(const T &x);
};


template<class T, class I>
sorted_array<T,I>::sorted_array(T *a0, I n0) {
	n = n0;
	a = new T[n];
	std::copy_n(a0, n, a);
}

template<class T, class I>
sorted_array<T,I>::~sorted_array() {
	delete[] a;
}

template<class T, class I>
I sorted_array<T,I>::search(const T &x) {
	I lo = 0;
	I hi = n;
	while (lo < hi) {
		I m = (lo + hi) / 2;
		if (x < a[m]) {
			hi = m;
		} else if (x > a[m]) {
			lo = m+1;
		} else {
			return m;
		}
	}
	return hi;
}

} // namespace fbs

#endif /* FBS_SORTED_ARRAY_H_ */
