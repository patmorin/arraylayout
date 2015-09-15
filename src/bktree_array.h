/*
 * base_array.h
 *
 *  Created on: 2015-05-01
 *      Author: morin
 */
#ifndef FBS_BKTREE_H
#define FBS_BKTREE_H

#include "btree_array.h"

namespace fbs{

/*
 * An implementation of btree array in which each block has size B*K
 */
template<unsigned B, unsigned K, typename T, typename I>
class bktree_array : public btree_array<B*K,T,I,true> {
protected:
	using btree_array<B*K,T,I,true>::a;
	using btree_array<B*K,T,I,true>::n;
	using btree_array<B*K,T,I,true>::child;

	template<unsigned int C>
	static const T* branchfree_inner_search(const T *base, const T x) {
		if (C <= 1) return base;
		const unsigned int half = C / 2;
		const T *current = &base[half];
		return branchfree_inner_search<C - half>((*current < x) ? current : base, x);
	}


public:
	template<typename ForwardIterator>
	bktree_array(ForwardIterator a0, I n0)
		: btree_array<B*K,T,I,true>(a0, n0) {};

	I search(T x) const;
};

template<unsigned B, unsigned K, typename T, typename I>
I __attribute__ ((noinline)) bktree_array<B,K,T,I>::search(T x) const {
	I j = n;
	I i = 0;
	while (i + B*K <= n) {
		for (int t = 0; t < K; t++)
			__builtin_prefetch(a+i+t*B);
		const T *base = &a[i];
		const T *pred = branchfree_inner_search<B*K>(base, x);
		unsigned int nth = (*pred < x) + pred - base;
		{
			/* nth == D*Q iff x > all values in block. */
			const T current = base[nth % (B*K)];
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


} // namespace fbs

#endif // FBS_BKTREE_H
