/*
 * vebarray.h
 *
 *  Created on: 2015-04-24
 *      Author: morin
 */

#ifndef FBS_VEB_ARRAY_H_
#define FBS_VEB_ARRAY_H_

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "base_array.h"

namespace fbs {

template<typename T, typename I>
class veb_array : public base_array<T,I> {
protected:
	using base_array<T,I>::a;
	using base_array<T,I>::n;

	I h;     // the height of the tree

	static const unsigned MAX_H = 32;

	typedef unsigned char h_type;
	struct dumdum {
		h_type h0, h1, dummy[2];
		I m0, m1;
	};
	dumdum s[MAX_H+1];

	static void sequencer(I h, dumdum *s, unsigned d);

	template<typename Iter>
	Iter copy_data(Iter a0, I *rtl, I path, unsigned d);

public:
	template<typename Iter>
	veb_array(Iter a0, I n0);

	~veb_array();

	I search(const T &x);
};

template<typename T, typename I>
void veb_array<T,I>::sequencer(I h, dumdum *s, unsigned d) {
	if (h == 0) return;
	I h0 = h/2;
	I h1 = h-h0-1;
	sequencer(h0, s, d);
	s[d+h0].h0 = h0;
	s[d+h0].m0 = (((I)2)<<h0)-1;
	s[d+h0].h1 = h1;
	s[d+h0].m1 = (((I)2)<<h1)-1;
	sequencer(h1, s, d+h0+1);
}

template<typename T, typename I>
template<typename Iter>
Iter veb_array<T,I>::copy_data(Iter a0, I *rtl, I path, unsigned d) {

	if (d > h || rtl[d] >= n) return a0;

	// visit left child
	path <<= 1;
	rtl[d+1] = rtl[d-s[d].h0] + s[d].m0 + (path&s[d].m0)*(s[d].m1);
	a0 = copy_data(a0, rtl, path, d+1);

	a[rtl[d]] = *a0++;

	// visit right child
	path += 1;
	rtl[d+1] = rtl[d-s[d].h0] + s[d].m0 + (path&s[d].m0)*(s[d].m1);
	a0 = copy_data(a0, rtl, path, d+1);

	return a0;
}


template<typename T, typename I>
template<typename Iter>
veb_array<T,I>::veb_array(Iter a0, I n0) {
	n = n0;

	// find smallest h such that sum_i=0^h 2^h >= n
	int m = 1;
	for (h = 0; m < n; h++, m += 1<<h);

	// build our magic sequence
	dumdum q = {(h_type)h, 0, {0, 0}, ((I)2<<h)-1, 1};
	std::fill_n(s, MAX_H+1, q);
	sequencer(h, s, 0);

	// allocate new array and copy data into it
	a = new T[n];
	I rtl[MAX_H+1];
	rtl[0] = 0;
	copy_data(a0, rtl, 0, 0);
}

template<typename T, typename I>
veb_array<T,I>::~veb_array() {
	delete[] a;
}

template<typename T, typename I>
I veb_array<T,I>::search(const T &x) {
	I rtl[MAX_H+1];
	I j = n;
	I i = 0;
	I p = 0;
	for (int d = 0; i < n; d++) {
		rtl[d] = i;
		if (x < a[i]) {
			p <<= 1;
			j = i;
		} else if (x > a[i]) {
			p = (p << 1) + 1;
		} else {
			return i;
		}
		i = rtl[d-s[d].h0] + s[d].m0 + (p&s[d].m0)*(s[d].m1);
	}
	return j;
}

} // namespace fbs

#endif /* FBS_VEB_ARRAY_H_ */
