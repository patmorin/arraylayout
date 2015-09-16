/*
 * base_array.h
 *
 *  Created on: 2015-05-01
 *      Author: morin
 */

#ifndef FBS_BASE_ARRAY_H_
#define FBS_BASE_ARRAY_H_

namespace fbs {

template<typename T, typename I>
class base_array {
protected:
	T *a;
	I n;
	static_assert(std::is_integral<I>::value,
			"template argument I must be an integral value");

public:
	base_array() { a = NULL; n = 0; };

	const T get_data(I i) {
#ifdef _DEBUG
		if (i < 0 || i >= n) {
			std::ostringstream ss;
			ss << "index " << i << " is out of bounds ({0,...," << n-1 << "})";
			throw std::out_of_range(ss.str());
		}
#endif
		return a[i];
	}
	const T operator[](I i) { return get_data(i); }
};

} // namespace fbs

#endif /* FBS_BASE_ARRAY_H_ */
