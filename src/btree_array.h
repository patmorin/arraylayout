/*
 * btree_array.h
 *
 *  Created on: 2015-04-24
 *      Author: morin
 */

#ifndef FBS_BTREE_ARRAY_H_
#define FBS_BTREE_ARRAY_H_

#include <algorithm>
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
template<unsigned B, typename T, typename I>
class btree_array : public base_array<T,I> {
protected:
	using base_array<T,I>::a;
	using base_array<T,I>::n;

	I child(unsigned c, I i) {
		return (B+1)*i + (c+1)*B;
	}

	template<class Iter>
	Iter copy_data(Iter a0, I i);

public:
	template<typename Iter>
	btree_array(Iter a0, I n0);

	~btree_array();

	I search(const T &x);

};

template<unsigned B, typename T, typename I>
template<typename Iter>
Iter btree_array<B,T,I>::copy_data(Iter a0, I i) {
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


template<unsigned B, typename T, typename I>
template<typename Iter>
btree_array<B, T,I>::btree_array(Iter a0, I n0) {
	if (n0-1 > std::numeric_limits<I>::max()/(B+1)-B) {
		std::ostringstream ss;
		ss << "array length " << n0 << " is too big, use a larger I class";
		throw std::out_of_range(ss.str());
	}
	n = n0;
	a = new T[n];
	copy_data(a0, 0);

}

template<unsigned B, typename T, typename I>
btree_array<B, T,I>::~btree_array() {
	delete[] a;
}

template<unsigned B, typename T, typename I>
I btree_array<B, T,I>::search(const T &x) {
	I j = n;
	I i = 0;
	while (i < n) {
		I lo = i;
		I hi = std::min(i+B, n);
		while (lo < hi) {
			I m = (lo + hi) / 2;
			if (x < a[m]) {
				hi = m;
				j = hi;
			} else if (x > a[m]) {
				lo = m+1;
			} else {
				return m;
			}
		}
		i = child((unsigned)(hi-i), i);
	}
	return j;
}

} // namespace fbs


#endif /* FBS_BTREE_ARRAY_H_ */
