/*
 * 2level_array.h
 *
 *  Created on: 2015-05-11
 */

#ifndef FBS_2LEVEL_ARRAY_H_
#define FBS_2LEVEL_ARRAY_H_

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <math.h>

#include "base_array.h"

namespace fbs {

template<typename T, typename I>
class level2_array : public base_array<T,I> {
protected:
	using base_array<T,I>::a;
	using base_array<T,I>::n;
        T *b;
        size_t sqrtN;

public:
	template<typename ForwardIterator>
	level2_array(ForwardIterator a0, I n0);
	~level2_array();
	I search(const T &x);
};


template<typename T, typename I>
template<typename ForwardIterator>
level2_array<T,I>::level2_array(ForwardIterator a0, I n0)
{
		n = n0;
		a = new T[n];
                b = nullptr;
		std::copy_n(a0, n, a);

                if (n > 16 * 1024) {
                  sqrtN = ceil(sqrt(n));
                  // Create the 2nd level array
                  b = new T[sqrtN - 1];
                  for (size_t i = 0; i < sqrtN-1; i++) {
                    size_t idx = (i + 1) * sqrtN - 1;
                    if (idx >= n) {
                      idx = n - 1;
                    }
                    b[i] = a[idx];
                  }
                }
}

template<typename T, typename I>
level2_array<T,I>::~level2_array() {
	delete[] a;
        delete[] b;
}

template<typename T, typename I>
I level2_array<T,I>::search(const T &x) {
  if (n <= 16 * 1024) {
    return std::lower_bound(a, a+n, x) - a;
  }
  auto it = std::equal_range(b, b + sqrtN - 1, x);
  size_t beg = (it.first - b) * sqrtN;
  size_t end = (it.second + 1 - b) * sqrtN;
  if (beg >= n) return n;
  if (end > n) { end = n; }
  return std::lower_bound(a+beg, a+end, x) - a;
}

} // namespace fbs

#endif /* FBS_2LEVEL_ARRAY_H_ */
