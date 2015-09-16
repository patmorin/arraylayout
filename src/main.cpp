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

#include "veb_array.h"
#include "eytzinger_array.h"
#include "sorted_array.h"
#include "btree_array.h"
#include "bktree_array.h"
#include "mixed_array.h"

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

// Make fake_numbers to respond correctly to is_integral and is_floating_point
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
	case 16:
		return "uint128";
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


// This is a fake sorted array class that doesn't store anything. Instead,
// it relies on the array only storing 1,3,5,...,2*n-1 to answer queries in
// constant time
template<typename T, typename I>
class fake_array  {
protected:
	I n;
public:
	template<typename ForwardIterator>
	fake_array(ForwardIterator a0, I n0) {
		(void)a0;
		n = n0;
	}
	I search(const T &x);
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

template<typename T, typename I>
I fake_array<T,I>::search(const T &x) {
	return std::min(n, (I)x/2);
}


// Build an array of size n and fill it with 0, 2, 4,...,2n-2
template<class T, class I>
T *build_and_fill(I n) {
	T *a = new T[n];
	for (I i = 0; i < n; i++)
		a[i] = 2*i+1;
	return a;
}


// Run tests that perform m searches on one array of size n
// Note: D is one of uniform_int_distribution or uniform_real_distribution
template<typename Array, typename T, typename I, typename D>
void run_test1_b(T *a, I n, I m, const std::string &name) {
        auto seed=232342;
	std::mt19937 re(seed);
	//std::minstd_rand re(seed);
	D ui(0, 2*n+2);

	std::cout << name << " " << type_name<T>() << " " << type_name<I>()
			<< " " << n << " " << m << " ";
	std::cout.flush();
	auto start = std::chrono::high_resolution_clock::now();
	Array aa(a, n);
	auto stop =  std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = stop - start;
	std::cout << elapsed.count() << " ";
	std::cout.flush();
	start = std::chrono::high_resolution_clock::now();
	T sum = 0;
	for (I i = 0; i < m; i++) {
		T x = ui(re);
		I j = aa.search(x);
		sum += (j < n) ? (int)aa.get_data(j) : -1;
	}
	stop = std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << elapsed.count() << " " << sum << std::endl;
}

// Next we use some traits magic to generate the right kind of random numbers,
// either integer or "real" depending on T.
template<typename Array, typename T, typename I>
class Tool { };

template<typename Array, typename I>
struct Tool<Array, std::uint32_t, I> {
	static void run_test1(std::uint32_t *a, I n, I m, const std::string &name) {
		run_test1_b<Array, std::uint32_t, I, std::uniform_int_distribution<std::uint32_t> >(a, n, m, name);
	}
};

template<typename Array, typename I>
struct Tool<Array, std::uint64_t, I> {
	static void run_test1(std::uint64_t *a, I n, I m, const std::string &name) {
		run_test1_b<Array, std::uint64_t, I, std::uniform_int_distribution<std::uint64_t> >(a, n, m, name);
	}
};

template<typename Array, typename I>
struct Tool<Array, float, I> {
	static void run_test1(float *a, I n, I m, const std::string &name) {
		run_test1_b<Array, float, I, std::uniform_real_distribution<float> >(a, n, m, name);
	}
};

template<typename Array, typename I>
struct Tool<Array, double, I> {
	static void run_test1(double *a, I n, I m, const std::string &name) {
		run_test1_b<Array, double, I, std::uniform_real_distribution<double> >(a, n, m, name);
	}
};

template<typename Array, unsigned S, typename I>
struct Tool<Array, fake_number<std::uint64_t,S>, I> {
	static void run_test1(fake_number<std::uint64_t,S> *a, I n, I m, const std::string &name) {
		run_test1_b<Array, fake_number<std::uint64_t,S>, I, std::uniform_int_distribution<std::uint32_t> >(a, n, m, name);
	}
};


// The cache line width (in bytes)
static const unsigned CACHE_LINE_WIDTH = 64;

// Our test driver
template<typename T, typename I>
void run_tests(I n, I m) {
	T *a = build_and_fill<T,I>(n);
	Tool<fake_array<T,I>,T,I>::run_test1(a, n, m, "fake");

	Tool<sorted_array<T,I>,T,I>::run_test1(a, n, m, "sorted");
	Tool<sorted_array_bf<T,I>,T,I>::run_test1(a, n, m, "sorted_bf");
	Tool<sorted_array_bfp<T,I>,T,I>::run_test1(a, n, m, "sorted_bfp");
	Tool<sorted_array_stl<T,I>,T,I>::run_test1(a, n, m, "sorted_stl");

	Tool<veb_array<T,I>,T,I>::run_test1(a, n, m, "veb");
	Tool<veb2_array<T,I>,T,I>::run_test1(a, n, m, "veb2");
	Tool<veb2_array<T,I,true>,T,I>::run_test1(a, n, m, "veb2e");

	Tool<eytzinger_array<T,I>,T,I>::run_test1(a, n, m, "eytzinger_branchy");
	Tool<eytzinger_array_bf<T,I>,T,I>::run_test1(a, n, m, "eytzinger_bf");
	Tool<eytzinger_array_bfp<T,I>,T,I>::run_test1(a, n, m, "eytzinger_bfp");
	Tool<eytzinger_array_bf<T,I,true>,T,I>::run_test1(a, n, m, "eytzinger_bf_a");

	Tool<eytzinger_array_bfp<T,I,true>,T,I>::run_test1(a, n, m, "eytzinger_bfp_a");
	Tool<eytzinger_array_bfpm<T,I,true>,T,I>::run_test1(a, n, m, "eytzinger_bfpm_a");
	Tool<mixed_array<T,I>,T,I>::run_test1(a, n, m, "esmixed");
	Tool<mixed_array_pf<T,I>,T,I>::run_test1(a, n, m, "esmixed_pf");
	Tool<eytzinger_array_unrolled<T,I>,T,I>::run_test1(a, n, m, "eytzinger_unrolled");

	Tool<eytzinger_array_deeppf<T,I,0,true>,T,I>::run_test1(a, n, m, "fetcher_0");
	Tool<eytzinger_array_deeppf<T,I,1,true>,T,I>::run_test1(a, n, m, "fetcher_1");
	Tool<eytzinger_array_deeppf<T,I,2,true>,T,I>::run_test1(a, n, m, "fetcher_2");

	const unsigned B = CACHE_LINE_WIDTH/sizeof(T);
	if (sizeof(I) > 4 || n <= 100000000)
		Tool<btree_array<2*B,T,I>,T,I>::run_test1(a, n, m, "btree32");
	Tool<btree_array_naive<B,T,I>,T,I>::run_test1(a, n, m, "btree16_naive");
	Tool<btree_array<B,T,I>,T,I>::run_test1(a, n, m, "btree16");
	Tool<btree_array<B/2,T,I>,T,I>::run_test1(a, n, m, "btree4");

	Tool<btree_array_bf<B,T,I>,T,I>::run_test1(a, n, m, "btree16_bf");
	Tool<btree_array_bfp<B,T,I>,T,I>::run_test1(a, n, m, "btree16_bfp");
	Tool<btree_array_bfp<B/2,T,I>,T,I>::run_test1(a, n, m, "btree8_bfp");
	Tool<btree_array_bfp<B/4,T,I>,T,I>::run_test1(a, n, m, "btree4_bfp");

	if (sizeof(I) > 4 || n <= 100000000)
		Tool<btree_array<2*B,T,I,true>,T,I>::run_test1(a, n, m, "btree32_a");
	Tool<btree_array_naive<B,T,I,true>,T,I>::run_test1(a, n, m, "btree16_naive_a");
	Tool<btree_array<B,T,I,true>,T,I>::run_test1(a, n, m, "btree16_a");
	Tool<btree_array<B/2,T,I,true>,T,I>::run_test1(a, n, m, "btree8_a");

	Tool<btree_array_bf<B,T,I,true>,T,I>::run_test1(a, n, m, "btree16_bf_a");
	Tool<bktree_array<B,1,T,I>,T,I>::run_test1(a, n, m, "bqtree16_1");
	Tool<bktree_array<B,2,T,I>,T,I>::run_test1(a, n, m, "bqtree16_2");
	Tool<bktree_array<B,3,T,I>,T,I>::run_test1(a, n, m, "bqtree16_3");
	Tool<bktree_array<B,4,T,I>,T,I>::run_test1(a, n, m, "bqtree16_4");
	Tool<bktree_array<B,5,T,I>,T,I>::run_test1(a, n, m, "bqtree16_5");
	Tool<bktree_array<B,6,T,I>,T,I>::run_test1(a, n, m, "bqtree16_6");
	Tool<bktree_array<B,7,T,I>,T,I>::run_test1(a, n, m, "bqtree16_7");
	Tool<bktree_array<B,8,T,I>,T,I>::run_test1(a, n, m, "bqtree16_8");
	Tool<bktree_array<B,9,T,I>,T,I>::run_test1(a, n, m, "bqtree16_9");
	Tool<bktree_array<B,10,T,I>,T,I>::run_test1(a, n, m, "bqtree16_10");
	Tool<bktree_array<B,11,T,I>,T,I>::run_test1(a, n, m, "bqtree16_11");
	Tool<bktree_array<B,12,T,I>,T,I>::run_test1(a, n, m, "bqtree16_12");
	Tool<bktree_array<B,13,T,I>,T,I>::run_test1(a, n, m, "bqtree16_13");
	Tool<bktree_array<B,14,T,I>,T,I>::run_test1(a, n, m, "bqtree16_14");
	Tool<bktree_array<B,15,T,I>,T,I>::run_test1(a, n, m, "bqtree16_15");
	Tool<bktree_array<B,16,T,I>,T,I>::run_test1(a, n, m, "bqtree16_16");


	delete[] a;
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
			<< "  <dtype> is in {uint32, uint64, float32, float64, uint128}"
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
	std::string dtypes[] = {"uint32", "float32", "uint64", "float64", "uint128"};
	std::string itypes[] = {"uint32", "uint64", "fast_uint32"};

	if (argc == 5) {
		for (dt = 0; dt < 5; dt++)
			if (dtypes[dt] == argv[1]) break;
		for (it = 0; it < 3; it++)
			if (itypes[it] == argv[2]) break;
		std::istringstream is_n(argv[3]);
		is_n >> n;
		std::istringstream is_m(argv[4]);
		is_m >> m;
	} else {
		usage(argv[0]);
		std::exit(-1);
	}
	if (dt < 0 || dt > 4 || it < 0 || it > 2) {
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

	else if (dt == 4 && it == 0)
		run_it<fake_number<std::uint64_t,16>,std::uint32_t>(n, m);
	else if (dt == 4 && it == 1)
		run_it<fake_number<std::uint64_t,16>,std::uint64_t>(n, m);
	else if (dt == 4 && it == 2)
		run_it<fake_number<std::uint64_t,16>,std::uint_fast32_t>(n, m);

	return 0;
}



