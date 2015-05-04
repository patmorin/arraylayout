/*
 * main.cpp
 *
 *  Created on: 2015-04-24
 *      Author: morin
 */

#include <chrono>
#include <random>
#include <cstdint>
#include <cstring>

#include "base_array.h"

#include "veb_array.h"
#include "eytzinger_array.h"
#include "sorted_array.h"
#include "btree_array.h"

using namespace fbs;



// This class represents a number (type T) with some auxilliary data
template<typename T, unsigned S>
class fake_number {
	T x;
	char buf[S-sizeof(T)];
public:
	fake_number() { };
	fake_number(int x0) { x = x0; };
	bool operator<(const fake_number<T,S>& y) const {
		return x < y.x;
	};
	bool operator>(const fake_number<T,S>& y) const {
		return x > y.x;
	};
	bool operator==(const fake_number<T,S>& y) const {
		return x == y.x;
	};
	operator int() const { return x; };
	fake_number<T,S>& operator+=(const fake_number<T,S>& y) {
		x += y.x;
		return *this;
	};
};

namespace std {
template<typename T, unsigned S>
struct is_integral<fake_number<T,S>> {
	static const bool value = std::is_integral<T>::value;
};
template<typename T, unsigned S>
struct is_floating_point<fake_number<T,S>> {
	static const bool value = std::is_floating_point<T>::value;
};
}


// What comes next is just a bunch of convenience functions for converting
// types into strings
template<class T>
const char *type_name() {
	switch(sizeof(T)) {
	case 1:
		return "unknown8";
	case 2:
		return "unknown16";
	case 4:
		return "unknown32";
	case 8:
		return "unknown64";
	}
	return "unknown";
}

template<>
const char *type_name<std::uint32_t>() {
	return "uint32";
}

template<>
const char *type_name<std::uint64_t>() {
	return "uint64";
}

template<>
const char *type_name<float>() {
	return "float32";
}

template<>
const char *type_name<double>() {
	return "float64";
}


// This is a fake sorted array class that doesn't store anything
template<typename T, typename I>
class fake_array  {
protected:
	I n;
public:
	fake_array(T *a0, I n0) {
		(void)a0;
		n = n0;
	}
	I search(const T &x) {
		return std::max((I)0, std::min(n, (I)x/2));
	}
	T get_data(const I &i) {
#ifdef _DEBUG
		if (i < 0 || i >= n) {
			std::ostringstream ss;
			ss << "index " << i << " is out of bounds ({0,...," << n-1 << "})";
			throw std::out_of_range(ss.str());
		}
#endif
		return (T)(2*i);
	}
};

// Build an array of size n and fill it with 0, 2, 4,...,2n-2
template<class T, class I>
T *build_and_fill(I n) {
	T *a = new T[n];
	for (I i = 0; i < n; i++)
		a[i] = 2*(i+1);
	return a;
}

// Run tests that perform m searches on n arrays, each of size n
template<typename A, typename T, typename I>
void run_test2(I n, I m, const std::string &name) {
	// Create n arrays of size n
	T *a = build_and_fill<T,I>(n);
	//std::vector<Array> ap(n, Array(a, n));
	A **ap = new A*[n];
	for (I i = 0; i < n; i++) 
		ap[i] = new A(a, n);

	auto seed = 23433;
	std::mt19937 re(23433);
	std::uniform_int_distribution<T> ui(0, 2*n+1);
	std::uniform_int_distribution<T> ui2(0, n-1);

	std::cout << "Performing " << m << " " << name << " NxN searches...";
	std::cout.flush();
	re.seed(seed);
	auto start = std::chrono::high_resolution_clock::now();
	T sum = 0;
	for (int i = 0; i < m; i++) {
		I q = ui2(re);
		T x = ui(re);
		I j = ap[q]->search(x);
		sum += (j < n) ? (int)ap[q]->get_data(j) : -1;
	}
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = stop - start;
	std::cout << "done in " << elapsed.count() << "s (sum = " << sum << ")"
			<< std::endl;

	for (int i = 0; i < n; i++) 
		delete ap[i];
	delete[] ap;
	delete[] a;
}

// Run tests that perform m searches on one array of size n
// Note: D is one of uniform_int_distribution or uniform_real_distribution
template<typename Array, typename T, typename I, typename D>
void run_test1_b(T *a, I n, I m, const std::string &name) {
	auto seed = 23433;
	std::mt19937 re(23433);
	D ui(0, 2*n+1);

	std::cout << "Building " << name << " array...";
	std::cout.flush();
	auto start = std::chrono::high_resolution_clock::now();
	Array aa(a, n);
	auto stop =  std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = stop - start;
	std::cout << "done (" << elapsed.count() << "s)" << std::endl;

	std::cout << "Performing " << m << " " << name << " plain searches...";
	std::cout.flush();
	re.seed(seed);
	start = std::chrono::high_resolution_clock::now();
	T sum = 0;
	for (int i = 0; i < m; i++) {
		T x = ui(re);
		I j = aa.search(x);
		sum += (j < n) ? (int)aa.get_data(j) : -1;
	}
	stop = std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done in " << elapsed.count() << "s (sum = " << sum << ")"
			<< std::endl;
}

// Use this for integral types
// Thanks to Erbureth: http://stackoverflow.com/a/19985238/1614328
template<typename Array, typename T, typename I>
void run_test1(T *a, I n, I m, const std::string &name,
		typename std::enable_if<std::is_integral<T>::value>::type* = 0) {
	run_test1_b<Array, T, I, std::uniform_int_distribution<T> >(a, n, m, name);
}

// Use this template for floating-point types.
template<typename Array, typename T, typename I>
void run_test1(T *a, I n, I m, const std::string &name,
		typename std::enable_if<std::is_floating_point<T>::value>::type* = 0) {
	run_test1_b<Array, T, I, std::uniform_real_distribution<T> >(a, n, m, name);
}


// The cache line width (in bytes)
static const unsigned CACHE_LINE_WIDTH = 64;

// Our test driver
template<typename T, typename I>
void run_tests(I n, I m) {
	std::cout << "======================================================="
			<< std::endl;
	std::cout << "Running tests with " << type_name<T>() << " data and "
			<< 8*sizeof(I) << "-bit indices (n = " << n << ")" << std::endl;

	T *a = build_and_fill<T,I>(n);
	run_test1<fake_array<T,I>,T,I>(a, n, m, "fake");
	run_test1<sorted_array<T,I>,T,I>(a, n, m, "binary");
	run_test1<veb_array<T,I>,T,I>(a, n, m, "veb");
	run_test1<eytzinger_array<T,I>,T,I>(a, n, m, "eytzinger");
	const unsigned b = CACHE_LINE_WIDTH/sizeof(T);
	std::ostringstream s;
	s << (b+1) << "-tree";
	run_test1<btree_array<64/sizeof(T),T,I>,T,I>(a, n, m, s.str());
	delete[] a;

//	std::cout << "=====" << std::endl;
//	run_test2<sorted_array<T,I>,T,I>(10000, 10000000, "sorted");
//	run_test2<veb_array<T,I>,T,I>(10000, 10000000, "veb");
//	run_test2<eytzinger_array<T,I>,T,I>(10000, 10000000, "eytzinger");
//	run_test2<btree_array<64/sizeof(T),T,I>,T,I>(10000, 10000000, "b-tree");
}

// Unsigned 32 bit integer
typedef std::uint32_t data_t;
// typedef double data_t;

// fastest unsigned integer with at least 32 bits
typedef std::uint_fast32_t index_t;


void usage(char *name) {
	std::cerr << "Usage: " << name << " <dtype> <itype> <n> <m>"
			<< std::endl
			<< "  where " << std::endl
			<< "  <dtype> is in {uint32, uint64, float32, float64, int128}"
			<< std::endl
			<< "  <itype> is in {uint32, uint64, fast_uint32}" << std::endl;
}

template<typename T, typename I>
void run_it(std::uint64_t n, std::uint64_t m) {
	if (n > std::numeric_limits<I>::max()) {
		std::ostringstream ss;
		ss << "array length " << n << " is too big, use a larger I class";
		throw std::out_of_range(ss.str());
	}
	if (m > std::numeric_limits<I>::max()) {
		std::ostringstream ss;
		ss << "number of searches " << m << " is too big, use a larger I class";
		throw std::out_of_range(ss.str());
	}
	run_tests<T,I>((I)n, (I)m);
}

int main(int argc, char *argv[]) {
	std::uint64_t n, m;
	int dt, it;
	std::string dtypes[] = {"uint32", "float32", "uint64", "float64", "int128"};
	std::string itypes[] = {"uint32", "uint64", "fast_uint32"};

	if (argc == 5) {
		for (dt = 0; dt < 5; dt++)
			if (dtypes[dt] == argv[1]) break;
		for (it = 0; it < 5; it++)
			if (itypes[it] == argv[2]) break;
		std::istringstream is_n(argv[3]);
		is_n >> n;
		std::istringstream is_m(argv[4]);
		is_m >> m;
	} else {
		usage(argv[0]);
		std::exit(-1);
	}

	if (dt == 0 && it == 0)
		run_it<std::uint32_t,std::uint32_t>(n, m);
	else if (dt == 0 && it == 1)
		run_it<std::uint32_t,std::uint64_t>(n, m);
	else if (dt == 0 && it == 2)
		run_it<std::uint32_t,std::uint_fast32_t>(n, m);

	else if (dt == 1 && it == 0)
		run_it<float,std::uint32_t>(n, m);
	else if (dt == 1 && it == 1)
		run_it<float,std::uint64_t>(n, m);
	else if (dt == 1 && it == 2)
		run_it<float,std::uint_fast32_t>(n, m);

	else if (dt == 2 && it == 0)
		run_it<std::uint64_t,std::uint32_t>(n, m);
	else if (dt == 2 && it == 1)
		run_it<std::uint64_t,std::uint64_t>(n, m);
	else if (dt == 2 && it == 2)
		run_it<std::uint64_t,std::uint_fast32_t>(n, m);

	else if (dt == 3 && it == 0)
		run_it<double,std::uint32_t>(n, m);
	else if (dt == 3 && it == 1)
		run_it<double,std::uint64_t>(n, m);
	else if (dt == 3 && it == 2)
		run_it<double,std::uint_fast32_t>(n, m);

//	else if (dt == 4 && it == 0)
//		run_it<fake_number<std::uint32_t,16>,std::uint32_t>(n, m);
//	else if (dt == 4 && it == 1)
//		run_it<fake_number<std::uint32_t,16>,std::uint64_t>(n, m);
//	else if (dt == 4 && it == 2)
//		run_it<fake_number<std::uint32_t,16>,std::uint_fast32_t>(n, m);

	return 0;
}



