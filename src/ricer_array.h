/*
 * ricer_array.h
 *
 *  Created on: 2015-04-24
 *      Author: morin
 */

#ifndef FBS_RICER_ARRAY_H_
#define FBS_RICER_ARRAY_H_

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <cassert>

#include <bitset>

#include "base_array.h"

namespace fbs {

template<typename T, typename I, bool aligned=false>
class ricer_array : public base_array<T,I> {
protected:
	using base_array<T,I>::a;
	using base_array<T,I>::n;

	// We always prefetch multiplier*i + offset
	static const I multiplier = 64/sizeof(T);
        static const unsigned char unrolled_iterations
        = multiplier == 0 ? 0 : 31 - __builtin_clz(multiplier);
	static const I offset = multiplier + (aligned ? 0 : multiplier/2 - 1);

        unsigned char rolled_iterations;
	template<typename ForwardIterator>
	ForwardIterator copy_data(ForwardIterator a0, I i);

public:
	ricer_array() { };

	template<typename ForwardIterator>
	ricer_array(ForwardIterator a0, I n0);

	~ricer_array();

	// FIXME: The next three should be protected
	I _branchy_search(T x) const ;

	template<bool prefetch>
	I _branchfree_search(T x) const ;

	template<bool prefetch>
	I _branchfree_search2(T x) const ;

        template<bool prefetch>
        I _unrolled_search(T x) const;


	I branchfree_search(T x) const { return _branchfree_search2<false>(x); };
	I branchfree_search2(T x) const { return _branchfree_search2<false>(x); };
	I branchfree_prefetch_search(T x) const { return _branchfree_search2<true>(x); };
	I branchfree_prefetch_search2(T x) const { return _branchfree_search2<true>(x); };

	I unrolled_search(T x) const { return _unrolled_search<false>(x); };
	I unrolled_prefetch_search(T x) const { return _unrolled_search<true>(x); };

	I search(T x) const { return _branchy_search(x); };
};

// An Eytzinger array with branch-free searches
template<typename T, typename I, bool aligned=false>
class ricer_array_bf : public ricer_array<T,I,aligned> {
protected:
	using ricer_array<T,I,aligned>::branchfree_search;

public:
	template<typename ForwardIterator>
	ricer_array_bf(ForwardIterator a0, I n0)
		: ricer_array<T,I,aligned>(a0, n0) {}
	I search(T x) const { return branchfree_search(x); };
};

// An Eytzinger array with branch-free searches and prefetching
template<typename T, typename I, bool aligned=false>
class ricer_array_bfp : public ricer_array<T,I,aligned> {
protected:
	using ricer_array<T,I,aligned>::branchfree_prefetch_search;

public:
	template<typename ForwardIterator>
	ricer_array_bfp(ForwardIterator a0, I n0)
		: ricer_array<T,I,aligned>(a0, n0) {}
	I search(T x) { return branchfree_prefetch_search(x); };
};

// An Eytzinger array with branch-free searches and prefetching
template<typename T, typename I, bool aligned=false>
class ricer_array_bfp2 : public ricer_array<T,I,aligned> {
protected:
	using ricer_array<T,I,aligned>::branchfree_prefetch_search2;

public:
	template<typename ForwardIterator>
	ricer_array_bfp2(ForwardIterator a0, I n0)
		: ricer_array<T,I,aligned>(a0, n0) {}
	I search(T x) { return branchfree_prefetch_search2(x); };
};


// An Eytzinger array with branch-free searches and no prefetching
template<typename T, typename I, bool aligned=false>
class ricer_array_bf2 : public ricer_array<T,I,aligned> {
protected:
	using ricer_array<T,I,aligned>::branchfree_search2;

public:
	template<typename ForwardIterator>
	ricer_array_bf2(ForwardIterator a0, I n0)
		: ricer_array<T,I,aligned>(a0, n0) {}
	I search(T x) { return branchfree_search2(x); };
};

template<typename T, typename I, bool aligned=false>
class ricer_array_unrolled : public ricer_array<T,I,aligned> {
protected:
	using ricer_array<T,I,aligned>::unrolled_search;
        using ricer_array<T,I,aligned>::multiplier;

public:
	template<typename ForwardIterator>
	ricer_array_unrolled(ForwardIterator a0, I n0)
		: ricer_array<T,I,aligned>(a0, n0)
        {
                if (n0 <= multiplier) {
                        std::copy_n(a0, n0, this->a);
                }
        }
	I search(T x) { return unrolled_search(x); };
};

template<typename T, typename I, bool aligned=false>
class ricer_array_unrolled_pf : public ricer_array<T,I,aligned> {
protected:
	using ricer_array<T,I,aligned>::unrolled_prefetch_search;
        using ricer_array<T,I,aligned>::multiplier;

public:
	template<typename ForwardIterator>
	ricer_array_unrolled_pf(ForwardIterator a0, I n0)
		: ricer_array<T,I,aligned>(a0, n0)
        {
                if (n0 <= multiplier) {
                        std::copy_n(a0, n0, this->a);
                }
        }
	I search(T x) { return unrolled_prefetch_search(x); };
};

template<typename T, typename I, bool aligned>
template<typename ForwardIterator>
ForwardIterator ricer_array<T,I,aligned>::copy_data(ForwardIterator a0, I i) {

	if (i >= n) return a0;

	// visit left child
	a0 = copy_data(a0, 2*i+1);

	// put data at the root
	a[i] = *a0++;

	// visit right child
	a0 = copy_data(a0, 2*i+2);

	return a0;
}


template<typename T, typename I, bool aligned>
template<typename ForwardIterator>
ricer_array<T,I,aligned>::ricer_array(ForwardIterator a0, I n0) {
	if (n0 > std::numeric_limits<I>::max()/2) {
		std::ostringstream ss;
		ss << "array length " << n0 << " is too big, use a larger I class";
		throw std::out_of_range(ss.str());
	}
	n = n0;

        for (rolled_iterations = 0;; rolled_iterations++) {
                I limit = ((I)1U
			   << rolled_iterations) - 1;

                if (limit >= n0) {
                        break;
                }
        }

        if (rolled_iterations <= unrolled_iterations) {
                rolled_iterations = 0;
        } else {
                rolled_iterations -= unrolled_iterations;
        }

	if (aligned) {
		assert(posix_memalign((void **)&a, 64, sizeof(T) * (n+1)) == 0);
		a++;
	} else {
		a = new T[n];
	}
	copy_data(a0, 0);
}

template<typename T, typename I, bool aligned>
ricer_array<T,I,aligned>::~ricer_array() {
	if (aligned) {
		free(a-1);
	} else {
		delete[] a;
	}
}

// Branchy code with no prefetching
template<typename T, typename I, bool aligned>
I __attribute__ ((noinline)) ricer_array<T,I,aligned>::_branchy_search(T x) const {
	I i = 0;
	while (i < n) {
		if (x < a[i]) {
			i = 2*i + 1;
		} else if (x > a[i]) {
			i = 2*i + 2;
		} else {
			return i;
		}
	}
	I j = (i+1) >> __builtin_ffs(~(i+1));
	return (j == 0) ? n : j-1;
}

// Branch-free code with or without prefetching
template<typename T, typename I, bool aligned>
template<bool prefetch>
I __attribute__ ((noinline)) ricer_array<T,I,aligned>::_branchfree_search(T x) const {
	I i = 0;
	while (i < n) {
		if (prefetch) __builtin_prefetch(a+(multiplier*i + offset));
		i = (x <= a[i]) ? (2*i + 1) : (2*i + 2);
	}
	I j = (i+1) >> __builtin_ffs(~(i+1));
	return (j == 0) ? n : j-1;
}

// Branch-free code with or without prefetching
template<typename T, typename I, bool aligned>
template<bool prefetch>
I __attribute__ ((noinline)) ricer_array<T,I,aligned>::_branchfree_search2(T x) const {
	I i = 0;
	while (i < n) {
		if (prefetch) __builtin_prefetch(a+(multiplier*i + offset));
		i = (x <= a[i]) ? (2*i + 1) : (2*i + 2);
	}
	I j = (i+1) >> __builtin_ffs(~(i+1));
	return (j == 0) ? n : j-1;
}

//#define RICE

#ifndef RICE
template<typename T, typename I, bool aligned>
template<bool prefetch>
I __attribute__ ((noinline)) ricer_array<T,I,aligned>::_unrolled_search(T x) const {
	I i = 0;
        I n = this->n;

        if (__builtin_expect(n <= multiplier, 0)) {
                const T *base = a;

                while (n > 1) {
                        I half = n / 2;
                        const T *next = base + half;

                        base = (*next < x) ? next : base;
                        n -= half;
                }

                return (*base < x) + base - a;
        }

	unsigned int d = rolled_iterations;
        if (__builtin_expect(d > 0, 1)) {
                do {
                        if (prefetch)
                                __builtin_prefetch(a+(multiplier*i + offset));
                        i = (x <= a[i]) ? (2*i + 1) : (2*i + 2);
                } while (--d);
        }

        switch (unrolled_iterations) {
        case 6:
                i = (x <= a[i]) ? (2*i + 1) : (2*i + 2);
        case 5:
                i = (x <= a[i]) ? (2*i + 1) : (2*i + 2);
        case 4:
                i = (x <= a[i]) ? (2*i + 1) : (2*i + 2);
        case 3:
                i = (x <= a[i]) ? (2*i + 1) : (2*i + 2);
        case 2:
                i = (x <= a[i]) ? (2*i + 1) : (2*i + 2);
        case 1:
                if (i < n) {
                        i = (x <= a[i]) ? (2*i + 1) : (2*i + 2);
                }
        }

        i++;
	I j = i >> (1 + __builtin_ctzl(~i));
	return (j == 0) ? n : j - 1;
}
#else
template<typename T, typename I, bool aligned>
template<bool prefetch>
I __attribute__ ((noinline)) ricer_array<T,I,aligned>::_unrolled_search(T x) const {
        size_t i = 0;
        size_t n = this->n * sizeof(T);

        unsigned int d = rolled_iterations;
        if (__builtin_expect(d > 0, 1)) {
                do {
                        if (prefetch)
                                __builtin_prefetch(&(((const char *)a)[multiplier*i + offset * sizeof(T)]));
                        i = (x <= *(const T*)((const char*)a + i)) ? (2*i + sizeof(T)) : (2*i + 2 * sizeof(T));
                } while (--d);
        }

        switch (unrolled_iterations) {
        case 6:
                i = (x <= *(const T*)((const char*)a + i)) ? (2*i + sizeof(T)) : (2*i + 2 * sizeof(T));
        case 5:
                i = (x <= *(const T*)((const char*)a + i)) ? (2*i + sizeof(T)) : (2*i + 2 * sizeof(T));
        case 4:
                i = (x <= *(const T*)((const char*)a + i)) ? (2*i + sizeof(T)) : (2*i + 2 * sizeof(T));
        case 3:
                i = (x <= *(const T*)((const char*)a + i)) ? (2*i + sizeof(T)) : (2*i + 2 * sizeof(T));
        case 2:
                i = (x <= *(const T*)((const char*)a + i)) ? (2*i + sizeof(T)) : (2*i + 2 * sizeof(T));
        case 1:
                if (__builtin_expect(i >= n, 0)) {
                        goto done;
                }
                i = (x <= *(const T*)((const char*)a + i)) ? (2*i + sizeof(T)) : (2*i + 2 * sizeof(T));
        }

done:
        I offset = (const T*)((const char *)a + i) - a;
	I j = (offset+1) >> __builtin_ffs(~(offset+1));
	return (j == 0) ? this->n : j-1;
}
#endif
} // namespace fbs

#endif /* FBS_RICER_ARRAY_H_ */
