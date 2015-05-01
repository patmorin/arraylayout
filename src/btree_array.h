/*
 * btree_array.h
 *
 *  Created on: 2015-04-24
 *      Author: morin
 */

#ifndef BTREEARRAY_H_
#define BTREEARRAY_H_

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

using std::cout;
using std::endl;

template<unsigned B, class T, class I>
class btree_array {
protected:
	T *a;    // the data
	I n;     // the length of a

	I child(unsigned c, I i) {
		return (B+1)*i + (c+1)*B;
	}
	I copy_data(T *a0, I i0, I i);

public:
	btree_array(T *a0, I n0);
	~btree_array();
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

template<unsigned B, class T, class I>
I btree_array<B,T,I>::copy_data(T *a0, I i0, I i) {
	if (i0 >= n || i >= n) return i0;

	for (unsigned c = 0; c < B+1; c++) {
		// visit c'th child
		i0 = copy_data(a0, i0, child(c,i));
		if (i0 < n) {
			cout << "a[" << i+c << "] <= " << "a0[" << i0 << "]" << endl;
			a[i+c] = a0[i0++];
		}
	}

	return i0;
}


template<unsigned B, class T, class I>
btree_array<B, T,I>::btree_array(T *a0, I n0) {
	n = n0;

	// allocate new array and copy data into it
	a = new T[n];
	copy_data(a0, 0, 0);

}

template<unsigned B, class T, class I>
btree_array<B, T,I>::~btree_array() {
	delete[] a;
}

template<unsigned B, class T, class I>
I btree_array<B, T,I>::search(const T &x) {
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



#endif /* BTREEARRAY_H_ */
