#ifndef FBS_HYBRID_ARRAY_H
#define FBS_HYBRID_ARRAY_H

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <memory>
#include <cassert>

#include <bitset>

#include "base_array.h"

namespace fbs {

template<typename T, typename I, bool aligned, bool prefetch>
class hybrid_array : public base_array<T,I> {
protected:
	using base_array<T,I>::a;
	using base_array<T,I>::n;

	I min_depth;
	I bfs_depth;
	I bfs_leaves;
	I sorted_leaves;
	enum { block_size = 64 / sizeof(T) };
	enum { min_size = block_size * block_size - 1 };

	template<typename ForwardIterator>
	void build_sorted(size_t index, ForwardIterator &src);

	template<typename ForwardIterator>
	void build(size_t index, unsigned int depth, ForwardIterator &src);

	template<typename ForwardIterator>
	ForwardIterator copy_data(ForwardIterator a0);

public:
	hybrid_array() {}

	template<typename ForwardIterator>
	hybrid_array(ForwardIterator a0, I n0);

	~hybrid_array();

	I search(T x) const;
};

template<typename T, typename I, bool aligned, bool prefetch>
template<typename ForwardIterator>
void hybrid_array<T,I,aligned,prefetch>::build_sorted(size_t index, ForwardIterator &src)
{
	if (index >= n) {
		return;
	}

	size_t n_leaves = std::min((size_t)block_size, (size_t)(n - index));
	std::copy_n(src, n_leaves, a + index);
	src += n_leaves;
	return;
}

template<typename T, typename I, bool aligned, bool prefetch>
template<typename ForwardIterator>
void hybrid_array<T,I,aligned,prefetch>::build(size_t index, unsigned int depth,
    ForwardIterator &src)
{
	assert(depth > 0);

	if (depth > 1) {
		build(2 * index + 1, depth - 1, src);
	}

	if (depth <= min_depth) {
		build_sorted(index * block_size + block_size - 1, src);
	}

	a[index] = *src;
	++src;

	if (depth > 1) {
		build(2 * index + 2, depth - 1, src);
	}

	return;
}

template<typename T, typename I, bool aligned, bool prefetch>
template<typename ForwardIterator>
ForwardIterator hybrid_array<T,I,aligned,prefetch>::copy_data(ForwardIterator a0)
{
	size_t depth;

	if (n < min_size) {
		bfs_depth = 0;
		bfs_leaves = 0;
		sorted_leaves = n;
		std::copy_n(a0, n, a);
		return a0 + n;
	}

	for (min_depth = 0; (1UL << min_depth) < block_size; min_depth++) {
		/* nothing */;
	}

	for (depth = min_depth; ; depth++) {
		size_t capacity = ((1UL << depth) - 1)
			+ block_size * ((1UL << depth) - (1UL << (depth - min_depth)));

		if (capacity >= n) {
			break;
		}
	}

	bfs_depth = depth;
	bfs_leaves = (1UL << depth) - 1;
	sorted_leaves = n - bfs_leaves;
	build(0, depth, a0);
	return a0;
}

template<typename T, typename I, bool aligned, bool prefetch>
template<typename ForwardIterator>
hybrid_array<T,I,aligned,prefetch>::hybrid_array(ForwardIterator a0, I n0) {
	if (n0 > std::numeric_limits<I>::max()/2) {
		std::ostringstream ss;
		ss << "array length " << n0 << " is too big, use a larger I class";
		throw std::out_of_range(ss.str());
	}
	n = n0;
	if (aligned) {
		assert(posix_memalign((void **)&a, 64, sizeof(T) * (n + 1)) == 0);
		a++;
	} else {
		a = new T[n];
	}

	copy_data(a0);
}

template<typename T, typename I, bool aligned, bool prefetch>
hybrid_array<T,I,aligned,prefetch>::~hybrid_array() {
	if (aligned) {
		free(a-1);
	} else {
		delete[] a;
	}
}

namespace {
template<typename T, size_t n>
const T *inner_search(const T *base, T x)
{
	if (n <= 1) {
		return base + (*base < x);
	}

	static const size_t half = n / 2;
	const T *next = base + half;

	base = (*next < x) ? next : base;
	return inner_search<T, n - half>(base, x);
}
}
	
template<typename T, typename I, bool aligned, bool prefetch>
I __attribute__ ((noinline)) hybrid_array<T,I,aligned,prefetch>::search(T x) const
{
	if (__builtin_expect(n < min_size, 0)) {
		const T *base = a;
		I n = this->n;

		if (n == 0) {
			return 0;
		}

		while (n > 1) {
			I half = n / 2;
			const T *next = base + half;
			
			base = (*next < x) ? next : base;
			n -= half;
		}

		return (*base < x) + base - a;
	}

	I i = 0;
	const T *a = this->a;
	unsigned int d = bfs_depth;
	do {
		if (prefetch) {
			__builtin_prefetch(&a[i * block_size + block_size], 0);
		}

		i = (x <= a[i]) ? (2*i + 1) : (2*i + 2);
	} while (--d);

	i++;

	I j = i >> (1 + __builtin_ctzl(~i));
	I children = j-- * block_size - 1;
	if (__builtin_expect((i & (i + 1)) == 0, 0)) {
		return n;
	}

	if (__builtin_expect(children - bfs_leaves >= sorted_leaves, 0)) {
		return j;
	}

	const T *base = a + children;
	const T *children_end;
	I n_children = n - children;

	if (__builtin_expect(block_size <= n_children, 1)) {
		children_end = base + block_size;
		base = inner_search<T, block_size>(base, x);
	} else {
		children_end = base + n_children;

		I n = n_children;
		while (n > 1) {
			I half = n / 2;
			const T *next = base + half;
			
			base = (*next < x) ? next : base;
			n -= half;
		}

		base += *base < x;
	}

	I ret = base - a;

	return (base >= children_end) ? j : ret;
}
} // namespace fbs

#endif /* FBS_HYBRID_ARRAY_H */
