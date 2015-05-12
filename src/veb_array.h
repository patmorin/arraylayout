/*
 * vebarray.h
 *
 *  Created on: 2015-04-24
 *      Author: morin
 */

#ifndef FBS_VEB_ARRAY_H_
#define FBS_VEB_ARRAY_H_

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "base_array.h"

namespace fbs {

template<typename T, typename I, bool early_termination = false>
class veb_array : public base_array<T,I> {
protected:
	using base_array<T,I>::a;
	using base_array<T,I>::n;

	I h;     // the height of the tree

	static const unsigned MAX_H = 32;

	struct dumdum {
		I h0, h1;
		I m0, m1;
	};
	dumdum s[MAX_H+1];

	/* Lookups need h0, h1 + 1. */
        I h0s[MAX_H + 1];
        I h1_1s[MAX_H + 1];

	static void sequencer(I h, dumdum *s, I *h0s, I *h1_1s, unsigned d);

	template<typename ForwardIterator>
	ForwardIterator copy_data(ForwardIterator a0, I *rtl, I path, unsigned d);

public:
	template<typename ForwardIterator>
	veb_array(ForwardIterator a0, I n0);

	~veb_array();

	I search(const T &x);
};

template<typename T, typename I, bool e>
void veb_array<T,I,e>::sequencer(I h, dumdum *s, I *h0s, I *h1_1s, unsigned d) {
	if (h == 0) return;
	I h0 = h/2;
	I h1 = h-h0-1;
	sequencer(h0, s, h0s, h1_1s, d);
	s[d+h0].h0 = h0;
        h0s[d+h0] = h0;
	s[d+h0].m0 = (((I)2)<<h0)-1;
	s[d+h0].h1 = h1;
        h1_1s[d+h0] = h1 + 1;
	s[d+h0].m1 = (((I)2)<<h1)-1;
	sequencer(h1, s, h0s, h1_1s, d+h0+1);
}

template<typename T, typename I, bool e>
template<typename ForwardIterator>
ForwardIterator veb_array<T,I, e>::copy_data(ForwardIterator a0, I *rtl, I path, unsigned d) {

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

template<typename T, typename I, bool e>
template<typename ForwardIterator>
veb_array<T,I,e>::veb_array(ForwardIterator a0, I n0) {
	n = n0;

	// find smallest h such that sum_i=0^h 2^h >= n
	int m = 1;
	for (h = 0; m < n; h++, m += 1<<h)
                ;

	// build our magic sequence
        {
                dumdum q = {(I)h, 0, ((I)2<<h)-1, 1};
                std::fill_n(s, MAX_H + 1, q);
        }

        std::fill_n(h0s, MAX_H + 1, (I)h);
        std::fill_n(h1_1s, MAX_H + 1, 1);
	sequencer(h, s, h0s, h1_1s, 0);

	// allocate new array and copy data into it
        int r = posix_memalign((void **)&a, 1UL << 21, sizeof(T) * n);
        assert(r == 0);
	I rtl[MAX_H+1];
	rtl[0] = 0;
	copy_data(a0, rtl, 0, 0);
}

template<typename T, typename I, bool e>
veb_array<T,I,e>::~veb_array() {
	free(a);
}

template<typename T, typename I, bool early_termination>
__attribute__((noinline))
I veb_array<T,I,early_termination>::search(const T &x) {
	I rtl[MAX_H+1];
	I j = n;
	I i = 0;
	I p = 0;
	for (int d = 0; i < n; d++) {
                const I h0 = h0s[d];
                const I h1_1 = h1_1s[d];
                const I m0 = ((I)2 << h0) - 1;

                const T current = a[i];
		rtl[d] = i;
                if (early_termination && current == x) {
                        return i;
                }

                j = (x <= current) ? i : j;
                p = (p << 1) + (x > current);
                I mask = p & m0;
		i = rtl[d - h0] + m0 + (mask << h1_1) - mask;
	}
	return j;
}

} // namespace fbs

#endif /* FBS_VEB_ARRAY_H_ */
