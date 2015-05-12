/*
 * sorted_array.h
 *
 *  Created on: 2015-04-24
 *      Author: morin
 */

#ifndef FBS_SORTED_ARRAY_H_
#define FBS_SORTED_ARRAY_H_

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "base_array.h"

namespace fbs {

template<typename T, typename I, bool early_termination = false>
class sorted_array : public base_array<T,I> {
protected:
	using base_array<T,I>::a;
	using base_array<T,I>::n;

public:
	template<typename ForwardIterator>
	sorted_array(ForwardIterator a0, I n0);
	~sorted_array();
	I search(const T x);
};


template<typename T, typename I, bool e>
template<typename ForwardIterator>
sorted_array<T,I,e>::sorted_array(ForwardIterator a0, I n0)
{
        n = n0;
        int r = posix_memalign((void **)&a, 1UL << 21, sizeof(T) * n);
        assert(r == 0);
        std::copy_n(a0, n, a);
}

template<typename T, typename I, bool e>
sorted_array<T,I,e>::~sorted_array() {
	free(a);
}

template<typename T, typename I, bool early_termination>
__attribute__((noinline))
I sorted_array<T,I,early_termination>::search(const T x) {
	const T *base = a;
	I n = this->n;

        while (n > 1) {
                I half = n / 2;
                const T *ptr = &base[half];
                const T current = *ptr;

                if (early_termination && current == x) {
                        return ptr - a;
                }

                base = (current < x) ? ptr : base;
                n -= half;
        }

	return (*base < x) + base - a;
}

} // namespace fbs

#endif /* FBS_SORTED_ARRAY_H_ */
