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

#include <type_traits>
#include "base_array.h"

using std::cout;
using std::endl;
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

	template<class ForwardIterator>
	ForwardIterator copy_data(ForwardIterator a0, I i);

public:
	template<typename ForwardIterator>
	btree_array(ForwardIterator a0, I n0);

	~btree_array();

	I search(T x);

};

template<unsigned B, typename T, typename I>
template<typename ForwardIterator>
ForwardIterator btree_array<B,T,I>::copy_data(ForwardIterator a0, I i) {
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
template<typename ForwardIterator>
btree_array<B, T,I>::btree_array(ForwardIterator a0, I n0) {
	if (n0-1 > std::numeric_limits<I>::max()/(B+1)-B) {
		std::ostringstream ss;
		ss << "array length " << n0 << " is too big, use a larger I class";
		throw std::out_of_range(ss.str());
	}
	n = n0;
	// FIXME: replace with std::align once gcc supports it
	assert(posix_memalign((void **)&a, 64, sizeof(T) * (n+1)) == 0);
	//a = new T[n];
	copy_data(a0, 0);

}

template<unsigned B, typename T, typename I>
btree_array<B, T,I>::~btree_array() {
	//delete[] a;
	free(a);
}

template<unsigned B, typename T, typename I>
I __attribute__ ((noinline)) btree_array<B, T,I>::search(T x) {
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

template<unsigned B, typename T, typename I>
class btree_eytzinger_array : public btree_array<B,T,I> {
protected:
	using btree_array<B,T,I>::a;
	using btree_array<B,T,I>::n;
	using btree_array<B,T,I>::child;

	T* copy_eytz_data(T *b0, T *b, unsigned i);
	void eytz_block(I i);

public:
	template<typename ForwardIterator>
	btree_eytzinger_array(ForwardIterator a0, I n0)
		: btree_array<B,T,I>(a0, n0) {
		for (I i = 0; i+B <= n; i += B) {
			eytz_block(i);
		}
	};
	I search(T x);
};

template<unsigned B, typename T, typename I>
T* btree_eytzinger_array<B,T,I>::copy_eytz_data(T *b0, T *b, unsigned i) {
	if (i >= B) return b0;

	// visit left child
	b0 = copy_eytz_data(b0, b, 2*i+1);

	// put data at the root
	b[i] = *b0++;

	// visit right child
	b0 = copy_eytz_data(b0, b, 2*i+2);

	return b0;
}

// Layout the btree block starting at a+i in an Eytzinger order
template<unsigned B, typename T, typename I>
void btree_eytzinger_array<B,T,I>::eytz_block(I i) {
	T buf[B];
//	cout << "i = " << i << endl;
	copy_eytz_data(a+i, buf, 0);
//	for (int j = 0; j < B; j++) {
//		cout << a[i+j] << ",";
//	}
//	cout << " => ";
//	for (int j = 0; j < B; j++) {
//		cout << buf[j] << ",";
//	}
//	cout << endl;
	std::copy_n(buf, B, a+i);
}

// Search in block, which is layed out in Eytzinger order and has
// size B.
template<unsigned B, typename T, unsigned i, unsigned j>
inline unsigned inner_eytzinger_search(T *block, T x) {
	if (i >= B) return j;
    if (x < block[i]) {
    	inner_eytzinger_search<B,T,2*i+1,i>(block, x);
    } else if (x > block[i]) {
    	inner_eytzinger_search<B,T,2*i+2,j>(block, x);
    } else {
    	return i;
    }
}

template<unsigned B, typename T, typename I>
I __attribute__ ((noinline)) btree_eytzinger_array<B,T,I>::search(T x) {
	I j = n;
	I i = 0;
	static const unsigned unwinder[] =
	{8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15, 0, 16};

	// Search on complete b-tree blocks
	while (i+B <= n) {
		T *b = &a[i];
		unsigned t = 0, j1 = B;
		for (int _ = 0; _ < 4; _++) {
			T current = b[t];
			I left = 2*t + 1;
			I right = 2*t + 2;
			j1 = (x <= current) ? t : j1;
			t = (x <= current) ? left : right;
		}
		j1 = (t == B-1) ? (x <= b[t] ? t : j1) : j1;
		j = j1 < B ? i+j1 : j;
		i = child(unwinder[j1], i);
	}

	// Search last (partial) block if necessary
	if (__builtin_expect(i <= n, 0)) {
		I lo = i;
		I hi = n;
		while (lo < hi) {
			I m = (lo + hi) / 2;
			if (x < a[m]) {
				hi = m;
				j = m;
			} else if (x > a[m]) {
				lo = m+1;
			} else {
				return m;
			}
		}
	}
	return j;
}




// This class is designed to be prefetch-friendly. If L is the cache
// line size and C=L/sizeo(T) is the number of values that fit into
// a cache line, then we should take B=sqrt(C).  Then, when we're accessing
// block i, all of its B children will fit into a single cache line that can
// be prefetched before we search block i.
template<unsigned B, typename T, typename I>
class btree_arraypf : public btree_array<B, T,I> {
protected:
	using btree_array<B,T,I>::a;
	using btree_array<B,T,I>::n;
	using btree_array<B,T,I>::child;

public:
	template<typename ForwardIterator>
	btree_arraypf(ForwardIterator a0, I n0)
		: btree_array<B,T,I>(a0, n0) {};
	I search(T x);
};

template<unsigned B, typename T, typename I>
I __attribute__ ((noinline)) btree_arraypf<B,T,I>::search(T x) {
	I j = n;
	I i = 0;
	while (i < n) {
		I lo = i;
		I hi = std::min(i+B, n);
		__builtin_prefetch(&a[child(0, i)]);
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

// A btree array with a hardcoded inner search
template<unsigned B, typename T, typename I>
class bfbtree_array : public btree_array<B, T,I> {
protected:
	using btree_array<B,T,I>::a;
	using btree_array<B,T,I>::n;
	using btree_array<B,T,I>::child;

public:
	template<typename ForwardIterator>
	bfbtree_array(ForwardIterator a0, I n0)
		: btree_array<B,T,I>(a0, n0) {};
	I search(T x);
};


template<unsigned B, typename T, typename I>
inline I inner_search2(const T *a, I i, T x) {
	if (B==0) return i;
	if (x <= a[i+B/2])
		return inner_search2<B/2>(a, i, x);
	return inner_search2<B-B/2-1>(a, i+B/2+1, x);
}

template<unsigned B, typename T, typename I>
I __attribute__ ((noinline)) bfbtree_array<B,T,I>::search(T x) {
	I j = n;
	I i = 0;
	while (i+B <= n) {
		I t = inner_search2<B>(a, i, x);
		j = t < i+B ? t : j;
		i = child((unsigned)(t-i), i);
	}
	if (__builtin_expect(i <= n, 0)) {
		// Now we're in the last block
		I lo = i;
		I hi = n;
		while (lo < hi) {
			I m = (lo + hi) / 2;
			if (x < a[m]) {
				hi = m;
				j = m;
			} else if (x > a[m]) {
				lo = m+1;
			} else {
				return m;
			}
		}
	}
	return j;
}

} // namespace fbs


#endif /* FBS_BTREE_ARRAY_H_ */
