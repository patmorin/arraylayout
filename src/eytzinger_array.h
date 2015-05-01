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

#include "base_array.h"

namespace fbs {

template<class T, class I>
class eytzinger_array : public base_array<T,I> {
protected:
	using base_array<T,I>::a;
	using base_array<T,I>::n;

	I copy_data(T *a0, I i0, I i);

public:
	eytzinger_array(T *a0, I n0);
	~eytzinger_array();
	I search(const T &x);
};

template<class T, class I>
I eytzinger_array<T,I>::copy_data(T *a0, I i0, I i) {

	if (i0 >= n || i >= n) return i0;

	// visit left child
	i0 = copy_data(a0, i0, 2*i+1);

	// put data at the root
	a[i] = a0[i0++];

	// visit right child
	i0 = copy_data(a0, i0, 2*i+2);

	return i0;
}


template<class T, class I>
eytzinger_array<T,I>::eytzinger_array(T *a0, I n0) {
	if (n0 > std::numeric_limits<I>::max()/2) {
		std::ostringstream ss;
		ss << "array length " << n0 << " is too big, use a larger I class";
		throw std::out_of_range(ss.str());
	}
	n = n0;
	a = new T[n];
	copy_data(a0, 0, 0);
}

template<class T, class I>
eytzinger_array<T,I>::~eytzinger_array() {
	delete[] a;
}

template<class T, class I>
I eytzinger_array<T,I>::search(const T &x) {
	I j = n;
	I i = 0;
	for (int d = 0; i < n; d++) {
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

} // namespace fbs


#endif /* FBS_EYTZINGER_ARRAY_H_ */
