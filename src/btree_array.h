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
#include <cassert>

#include <type_traits>
#include "base_array.h"

using std::cout;
using std::endl;
using std::min;

namespace fbs {

/*
 * btree_array
 */
template<unsigned B, typename T, typename I, bool aligned=false>
class btree_array : public base_array<T,I> {
protected:
	using base_array<T,I>::a;
	using base_array<T,I>::n;

	static I child(unsigned c, I i) {
		return (B+1)*i + (c+1)*B;
	}

	template<class ForwardIterator>
	ForwardIterator copy_data(ForwardIterator a0, I i);

	template<unsigned int Q>
	const T* branchfree_inner_search(const T *base, const T x) const {
		if (Q <= 1) return base;
		const unsigned int half = Q / 2;
		const T *current = &base[half];
		return branchfree_inner_search<Q - half>((*current < x) ? current : base, x);
	}

	template<unsigned Q>
	I branchy_inner_search(const T *a, I i, T x) const {
		if (Q==0) return i;
		if (x <= a[i+Q/2])
			return branchy_inner_search<Q/2>(a, i, x);
		return branchy_inner_search<Q-Q/2-1>(a, i+Q/2+1, x);
	}

public:
	template<typename ForwardIterator>
	btree_array(ForwardIterator a0, I n0);
	~btree_array();

	template<bool prefetch>
	I branchfree_search_x(T x) const;

	I branchy_search(T x) const;
	I branchfree_search(T x) const { return branchfree_search_x<false>(x); };
	I branchfree_prefetch_search(T x) const { return branchfree_search_x<true>(x); };
	I search(T x) const { return branchy_search(x);	};
};

template<unsigned B, typename T, typename I, bool aligned=false>
class btree_array_bf : public btree_array<B,T,I,aligned> {
protected:
	using btree_array<B,T,I,aligned>::branchfree_search;
public:
	template<typename ForwardIterator>
	btree_array_bf(ForwardIterator a0, I n0)
		: btree_array<B,T,I,aligned>(a0, n0) {};
	I search(T x) const { return branchfree_search(x);	};
};

template<unsigned B, typename T, typename I, bool aligned=false>
class btree_array_bfp : public btree_array<B,T,I,aligned> {
protected:
	using btree_array<B,T,I,aligned>::branchfree_prefetch_search;
public:
	template<typename ForwardIterator>
	btree_array_bfp(ForwardIterator a0, I n0)
		: btree_array<B,T,I,aligned>(a0, n0) {};
	I search(T x) const { return branchfree_prefetch_search(x);	};
};


template<unsigned B, typename T, typename I, bool aligned>
template<typename ForwardIterator>
ForwardIterator btree_array<B,T,I,aligned>::copy_data(ForwardIterator a0, I i) {
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


template<unsigned B, typename T, typename I, bool aligned>
template<typename ForwardIterator>
btree_array<B,T,I,aligned>::btree_array(ForwardIterator a0, I n0) {
	if (n0-1 > std::numeric_limits<I>::max()/(B+1)-B) {
		std::ostringstream ss;
		ss << "array length " << n0 << " is too big, use a larger I class";
		throw std::out_of_range(ss.str());
	}
	n = n0;
	if (aligned) {
		// FIXME: replace with std::align once gcc supports it
		assert(posix_memalign((void **)&a, 64, sizeof(T) * (n+1)) == 0);
	} else {
		a = new T[n];
	}
	copy_data(a0, 0);

}

template<unsigned B, typename T, typename I, bool aligned>
btree_array<B,T,I,aligned>::~btree_array() {
	if (aligned) {
		free(a);
	} else {
		delete[] a;
	}
}

// branchy inner serach
template<unsigned B, typename T, typename I, bool aligned>
I __attribute__ ((noinline)) btree_array<B,T,I,aligned>::branchy_search(T x) const {
	I j = n;
	I i = 0;
	while (i + B <= n) {
		I t = branchy_inner_search<B>(a, i, x);
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

// branch-free search (with or without prefetching)
template<unsigned B, typename T, typename I, bool aligned>
template<bool prefetch>
I __attribute__ ((noinline)) btree_array<B,T,I,aligned>::branchfree_search_x(T x) const {
	I j = n;
	I i = 0;
	while (i + B <= n) {
		if (prefetch) __builtin_prefetch(a+child(i, B/2), 0, 0);
		const T *base = &a[i];
		const T *pred = branchfree_inner_search<B>(base, x);
		unsigned int nth = (*pred < x) + pred - base;
		{
			/* nth == B iff x > all values in block. */
			const T current = base[nth % B];
			I next = i + nth;
			j = (current >= x) ? next : j;
		}
		i = child(nth, i);
	}
	if (__builtin_expect(i < n, 0)) {
		// last (partial) block
		const T *base = &a[i];
		I m = n - i;
		while (m > 1) {
			I half = m / 2;
			const T *current = &base[half];

			base = (*current < x) ? current : base;
			m -= half;
		}

		I ret = (*base < x) + base - a;
		return (ret == n) ? j : ret;
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
	copy_eytz_data(a+i, buf, 0);
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

} // namespace fbs
#endif /* FBS_BTREE_ARRAY_H_ */
