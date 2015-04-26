/*
 * vebarray.h
 *
 *  Created on: 2015-04-24
 *      Author: morin
 */

#ifndef VEBARRAY_H_
#define VEBARRAY_H_

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

using std::cout;
using std::endl;

template<class T, class I>
class veb_array {
protected:
	T *a;    // the data
	I n;     // the length of a
	I h;     // the height of the tree

	static const int MAX_H = 32;

	struct dumdum {
		I h0, h1;
	};
	dumdum s[MAX_H];

	static void sequencer(I h, dumdum *s, unsigned d) {
		if (h == 0) return;
		I h0 = h/2;
		I h1 = h-h0-1;
		sequencer(h0, s, d);
		s[d+h0].h0 = h0;
		s[d+h0].h1 = h1;
		sequencer(h1, s, d+h0+1);
	}

	I copy_data(T *a0, I *rtl, I i, I path, unsigned d) {

		if (d > h || rtl[d] >= n || i >= n) return i;
		// cout << "d = " << d << ", rtl[d] = " << rtl[d] << endl;

		// visit left child
		path *= 2;
		I mask = (1 << (s[d].h0+1))-1;
		rtl[d+1] = rtl[d-s[d].h0] + (2<<s[d].h0)-1 + (path&mask)*((2<<s[d].h1)-1);
		i = copy_data(a0, rtl, i, path, d+1);

		// cout << "===== a[" << rtl[d] << "] <- " << a0[i] << endl;
		// copy data into current node
		a[rtl[d]] = a0[i++];

		// visit right child
		path += 1;
		rtl[d+1] = rtl[d-s[d].h0] + (2<<s[d].h0)-1 + (path&mask)*((2<<s[d].h1)-1);
		i = copy_data(a0, rtl, i, path, d+1);

		return i;
	}

public:
	veb_array(T *a0, I n0) {
		this->n = n0;

		int m = 1;
		for (h = 0; m < n; h++, m += 1<<h);

		this->a = new T[n];

		dumdum q = {h, 0};
		std::fill_n(s, MAX_H+1, q); // to get SIGFAULTs
		sequencer(h, s, 0);

		I rtl[MAX_H+1];
		std::fill_n(rtl, MAX_H+1, 32000); // to get SIGFAULTs

		rtl[0] = 0;
		copy_data(a0, rtl, 0, 0, 0);
	}

	~veb_array() {
		delete[] a;
	}

	I search(const T &x) {
		I rtl[MAX_H+1];
		//dumdum s[MAX_H+1];
		//std::copy_n(this->s, h+1, s);

		I j = n;
		I i = 0;
		I p = 0;
		for (int d = 0; i < n; d++) {
			rtl[d] = i;
			if (x < a[i]) {
				p <<= 1;
				j = i;
			} else if (x > a[i]) {
				p = (p << 1) | 1;
			} else {
				return i;
			}
			I m = (1 << (s[d].h0+1))-1;
			I a0 = d-s[d].h0;
			I a1 = (2<<s[d].h0)-1;
			I a2 = p&m;
			I a3 = a2<<(s[d].h1+1);
			i = rtl[a0] + a1 + a3 - a2;
		}
		return j;
	}

	T get_data(const I &i) {
		if (i < 0 || i >= n) {
			std::ostringstream ss;
			ss << "index " << i << " is out of bounds ({0,...," << n-1 << "})";
			throw std::out_of_range(ss.str());
		}
		return a[i];

	}
};



#endif /* VEBARRAY_H_ */
