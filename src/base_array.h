/*
 * base_array.h
 *
 *  Created on: 2015-05-01
 *      Author: morin
 */

#ifndef FBS_BASE_ARRAY_H_
#define FBS_BASE_ARRAY_H_

namespace fbs {

template<class T, class I>
class base_array {
protected:
	T *a;
	I n;

public:
	base_array() { a = NULL; n = 0; };

	const T& get_data(const I &i) {
#ifdef _DEBUG
		if (i < 0 || i >= n) {
			std::ostringstream ss;
			ss << "index " << i << " is out of bounds ({0,...," << n-1 << "})";
			throw std::out_of_range(ss.str());
		}
#endif
		return a[i];
	}
};

} // namespace fbs

#endif /* FBS_BASE_ARRAY_H_ */
