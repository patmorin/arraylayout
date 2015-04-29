/*
 * bfsarray.h
 *
 *  Created on: 2015-04-24
 *      Author: morin
 */

#ifndef BFSARRAY_H_
#define BFSARRAY_H_

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

using std::cout;
using std::endl;

template<class T, class I>
class bfs_array {
protected:
	T *a;    // the data
	I n;     // the length of a

	I copy_data(T *a0, I i0, I i);

public:
	bfs_array(T *a0, I n0);
	~bfs_array();
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
I bfs_array<T,I>::copy_data(T *a0, I i0, I i) {

	if (i0 >= n) return i0;

	// visit left child
	i0 = copy_data(a0, i0, 2*i+1);

	// put data at the root
	a[i] = a0[i0++];

	// visit right child
	i0 = copy_data(a0, i0, 2*i+2);

	return i0;
}


template<class T, class I>
bfs_array<T,I>::bfs_array(T *a0, I n0) {
	n = n0;

	// allocate new array and copy data into it
	a = new T[n];
	copy_data(a0, 0, 0);
}

template<class T, class I>
bfs_array<T,I>::~bfs_array() {
	delete[] a;
}

template<class T, class I>
I bfs_array<T,I>::search(const T &x) {
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



#endif /* BFSARRAY_H_ */
