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
#include <bitset>
#include <stdexcept>

using std::cout;
using std::endl;
using std::string;
using std::ostringstream;
using std::bitset;

template<class T, class I>
class veb_array {
protected:

	class my_sequencer {
	protected:
		static const int w = 8*sizeof(I);
		I h, i;
		I path, depth, parity, label;

		static string bin_fmt(int x, int d) {
			bitset<8> bsx(x);
			ostringstream os;
			os << bsx;
			return os.str().substr(8-d,d);
		}

		static string bin_fmt_r(int x, int d) {
			string s = bin_fmt(x, d);
			reverse(s.begin(), s.end());
			return s;
		}

	public:
		my_sequencer(I h0) {
			cout << "***h = " << h0 << endl;
			h = h0;
			label = 0;
			parity = h0;   // the parities of the labels on the r-t-l path
			path = 0;     // an encoding of the root-to-leaf path
			depth = w - __builtin_clz(h0);
			i = 0;
		}

		I next() {
			// walk up the right roof of the current subtree
			int t1s = __builtin_clz(~(path<<(w-depth)));
			int mask = (1<<depth)-1;
			depth -= t1s;
			int plus_ones = parity >> depth;
			int plus_twos = ((~parity & mask) >> depth) << 1;
			label += plus_ones + plus_twos;
			parity &= (1<<depth)-1;
			path &= (1<<depth)-1;

			// now step up to the crotch (from left child)
			label = (label << 1) | ((parity >> (depth-1)) & 1);
			int retval = label;
			cout << "retval = " << retval << endl;

			// step down to right child of crotch
			path |= 1 << (depth-1);
			label = (label-1)>>1;

			// walk down the left roof
			int down = label == 0 ? 0 : w - __builtin_clz(label);
			parity |= label << depth;
			depth += down;
			label = 0;

		    cout << "label = " << label << endl;
			cout << "depth = " << depth << endl;
			cout << "path = " << bin_fmt_r(path, depth) << endl;
			cout << "parity = " << bin_fmt_r(parity, depth) << endl;

			return retval;
		}
	};


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

	I copy_data(T *a0, I *rtl, I i, I path, unsigned d);

public:
	veb_array(T *a0, I n0);
	~veb_array();
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
I veb_array<T,I>::copy_data(T *a0, I *rtl, I i, I path, unsigned d) {

	if (d > h || rtl[d] >= n || i >= n) return i;

	// visit left child
	path <<= 1;
	I mask = (1 << (s[d].h0+1))-1;
	rtl[d+1] = rtl[d-s[d].h0] + (2<<s[d].h0)-1 + (path&mask)*((2<<s[d].h1)-1);
	i = copy_data(a0, rtl, i, path, d+1);

	a[rtl[d]] = a0[i++];

	// visit right child
	path += 1;
	rtl[d+1] = rtl[d-s[d].h0] + (2<<s[d].h0)-1 + (path&mask)*((2<<s[d].h1)-1);
	i = copy_data(a0, rtl, i, path, d+1);

	return i;
}


template<class T, class I>
veb_array<T,I>::veb_array(T *a0, I n0) {
	this->n = n0;

	int m = 1;
	for (h = 0; m < n; h++, m += 1<<h);
	// h = 0xffffffff >> __builtin_clz(h); // FIXME: portability
	cout << "h = " << h << endl;

	this->a = new T[n];

	dumdum q = {h, 0};
	std::fill_n(s, MAX_H+1, q); // to get SIGFAULTs
	sequencer(h, s, 0);

	I rtl[MAX_H+1];
	std::fill_n(rtl, MAX_H+1, 32000); // to get SIGFAULTs

	rtl[0] = 0;
	copy_data(a0, rtl, 0, 0, 0);
}

template<class T, class I>
veb_array<T,I>::~veb_array() {
	delete[] a;
}

template<class T, class I>
I veb_array<T,I>::search(const T &x) {
	I rtl[MAX_H+1];

	my_sequencer seq(h);
	for (int d = 0; d < h; d++) {
		cout << "d = " << d << ", seq[d] = " << seq.next() << endl;
	}
	exit(0);
	I j = n;
	I i = 0;
	I p = 0;
	for (int d = 0; i < n; d++) {
		cout << "d = " << d << ", seq[d] = " << seq.next() << endl;
		rtl[d] = i;
		if (x < a[i]) {
			p <<= 1;
			j = i;
		} else if (x > a[i]) {
			p = (p << 1) + 1;
		} else {
			return i;
		}
		I m = (1 << (s[d].h0+1))-1;
		i = rtl[d-s[d].h0] + (2<<s[d].h0)-1 + (p&m)*((2<<s[d].h1)-1);
	}
	return j;
}



#endif /* VEBARRAY_H_ */
