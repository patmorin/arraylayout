/*
 * sorted_array.h
 *
 *  Created on: 2015-04-24
 *      Author: morin
 */

#ifndef SORTEDARRAY_H_
#define SORTEDARRAY_H_

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

using std::cout;
using std::endl;

template<class T, class I>
class sorted_array {
protected:
	T *a;    // the data
	I n;     // the length of a

public:
	sorted_array(T *a0, I n0);
	~sorted_array();
	I search(const T &x);

	const T& get_data(const I &i) {
		if (i < 0 || i >= n) {
			std::ostringstream ss;
			ss << "index " << i << " is out of bounds ({0,...," << n-1 << "})";
			throw std::out_of_range(ss.str());
		}
		return a[i];

	}
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



#endif /* SORTEDARRAY_H_ */
