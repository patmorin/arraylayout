/*
 * main-mt.cpp
 *
 *  Created on: 2015-04-24
 *      Author: morin
 *  About:
 *  	This is just a giant copy of main.cpp with some small modifications
 *  	to do multithreaded tests.  If anyone cared about maitainability this
 *  	would get merged into main.cpp.
 */

#include <chrono>
#include <random>
#include <cstdint>
#include <cstring>
#include <vector>
#include <thread>

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
	case 16:
		return "int128";
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
	return std::max((I)0, std::min(n, (I)(x+1)/2));
}


// Build an array of size n and fill it with 0, 2, 4,...,2n-2
template<class T, class I>
T *build_and_fill(I n) {
	T *a = new T[n];
	for (I i = 0; i < n; i++)
		a[i] = 2*i+1;
	return a;
}

std::uint64_t dummy;

template<typename Array, typename T, typename I, typename D>
void kicker(Array& aa, int k, I n, I m) {
	auto seed=232342+k;
    //std::cout << k;
	std::mt19937 re(seed);
	D ui(0, 2*n+1);
	T sum = 0;
	for (I i = 0; i < m; i++) {
		T x = ui(re);
		I j = aa.search(x);
		sum += (j < n) ? (int)aa.get_data(j) : -1;
	}
	dummy += sum;
}

template<typename Array, typename T, typename I, typename D>
void run_test1_b(T *a, I n, I m, I nthreads, const std::string &name) {
	std::vector<std::thread> threads;

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
	for (I k = 0; k < nthreads; k++)
		threads.push_back(std::thread(kicker<Array,T,I,D>, std::ref(aa), k, n, m));
	for (auto &th : threads) th.join();
	stop = std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << " " << elapsed.count() << " mt" << std::endl;
}


// Next we use some traits magic to generate the right kind of random numbers,
// either integer or "real" depending on T.
template<typename Array, typename T, typename I>
class Tool { };

template<typename Array, typename I>
struct Tool<Array, std::uint32_t, I> {
	static void run_test1(std::uint32_t *a, I n, I m, I nthreads, const std::string &name) {
		run_test1_b<Array, std::uint32_t, I, std::uniform_int_distribution<std::uint32_t> >(a, n, m, nthreads, name);
	}
};

template<typename Array, typename I>
struct Tool<Array, std::uint64_t, I> {
	static void run_test1(std::uint64_t *a, I n, I m, I nthreads, const std::string &name) {
		run_test1_b<Array, std::uint64_t, I, std::uniform_int_distribution<std::uint64_t> >(a, n, m, nthreads, name);
	}
};

template<typename Array, typename I>
struct Tool<Array, float, I> {
	static void run_test1(float *a, I n, I m, I nthreads, const std::string &name) {
		run_test1_b<Array, float, I, std::uniform_real_distribution<float> >(a, n, m, nthreads, name);
	}
};

template<typename Array, typename I>
struct Tool<Array, double, I> {
	static void run_test1(double *a, I n, I m, I nthreads, const std::string &name) {
		run_test1_b<Array, double, I, std::uniform_real_distribution<double> >(a, n, m, nthreads, name);
	}
};

template<typename Array, unsigned S, typename I>
struct Tool<Array, fake_number<std::uint32_t,S>, I> {
	static void run_test1(fake_number<std::uint32_t,S> *a, I n, I m, I nthreads, const std::string &name) {
		run_test1_b<Array, fake_number<std::uint32_t,S>, I, std::uniform_int_distribution<std::uint32_t> >(a, n, m, nthreads, name);
	}
};


// The cache line width (in bytes)
static const unsigned CACHE_LINE_WIDTH = 64;

// Our test driver
template<typename T, typename I>
void run_tests(I n, I m, I nthreads) {
	T *a = build_and_fill<T,I>(n);
	Tool<fake_array<T,I>,T,I>::run_test1(a, n, m, nthreads, "fake");

	Tool<sorted_array<T,I>,T,I>::run_test1(a, n, m, nthreads, "sorted");
	Tool<sorted_array_bf<T,I>,T,I>::run_test1(a, n, m, nthreads, "sorted_bf");
	Tool<sorted_array_bfp<T,I>,T,I>::run_test1(a, n, m, nthreads, "sorted_bfp");

	Tool<veb_array<T,I>,T,I>::run_test1(a, n, m, nthreads, "veb");

	Tool<eytzinger_array<T,I>,T,I>::run_test1(a, n, m, nthreads, "eytzinger_branchy");
	Tool<eytzinger_array_bf<T,I>,T,I>::run_test1(a, n, m, nthreads, "eytzinger_bf");
	Tool<eytzinger_array_bfp<T,I>,T,I>::run_test1(a, n, m, nthreads, "eytzinger_bfp");
	Tool<eytzinger_array_bf<T,I,true>,T,I>::run_test1(a, n, m, nthreads, "eytzinger_bf_a");
	Tool<eytzinger_array_bfp<T,I,true>,T,I>::run_test1(a, n, m, nthreads, "eytzinger_bfp_a");

	const unsigned B = CACHE_LINE_WIDTH/sizeof(T);
	if (sizeof(I) > 4 || n <= 100000000)
		Tool<btree_array<2*B,T,I>,T,I>::run_test1(a, n, m, nthreads, "btree32");
	Tool<btree_array<B,T,I>,T,I>::run_test1(a, n, m, nthreads, "btree16");
	Tool<btree_array<B/2,T,I>,T,I>::run_test1(a, n, m, nthreads, "btree4");

	Tool<btree_array_bf<B,T,I>,T,I>::run_test1(a, n, m, nthreads, "btree16_bf");
	Tool<btree_array_bfp<B,T,I>,T,I>::run_test1(a, n, m, nthreads, "btree16_bfp");
	Tool<btree_array_bfp<B/2,T,I>,T,I>::run_test1(a, n, m, nthreads, "btree8_bfp");
	Tool<btree_array_bfp<B/4,T,I>,T,I>::run_test1(a, n, m, nthreads, "btree4_bfp");

	if (sizeof(I) > 4 || n <= 100000000)
		Tool<btree_array<2*B,T,I,true>,T,I>::run_test1(a, n, m, nthreads, "btree32_a");
	Tool<btree_array<B,T,I,true>,T,I>::run_test1(a, n, m, nthreads, "btree16_a");
	Tool<btree_array<B/2,T,I,true>,T,I>::run_test1(a, n, m, nthreads, "btree8_a");

	Tool<btree_array_bf<B,T,I,true>,T,I>::run_test1(a, n, m, nthreads, "btree16_bf_a");
	Tool<btree_array_bfp<B,T,I,true>,T,I>::run_test1(a, n, m, nthreads, "btree16_bfp_a");
	Tool<btree_array_bfp<B/2,T,I,true>,T,I>::run_test1(a, n, m, nthreads, "btree8_bfp_a");
	Tool<btree_array_bfp<B/4,T,I,true>,T,I>::run_test1(a, n, m, nthreads, "btree4_bfp_a");

	delete[] a;
}

// Unsigned 32 bit integer
typedef std::uint32_t data_t;
// typedef double data_t;

// fastest unsigned integer with at least 32 bits
typedef std::uint_fast32_t index_t;


void usage(char *name) {
	std::cerr << "Usage: " << name << " <dtype> <itype> <n> <m> [<nthreads>]"
			<< std::endl
			<< "  where " << std::endl
			<< "  <dtype> is in {uint32, uint64, float32, float64, int128}"
			<< std::endl
			<< "  <itype> is in {uint32, uint64, fast_uint32}" << std::endl;
}

template<typename T, typename I>
void run_it(std::uint64_t n, std::uint64_t m, std::uint64_t nthreads) {
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
	run_tests<T,I>((I)n, (I)m, (I)nthreads);
}

int main(int argc, char *argv[]) {
	std::uint64_t n, m, nthreads;
	int dt = 0, it = 1;
	std::string dtypes[] = {"uint32", "float32", "uint64", "float64", "int128"};
	std::string itypes[] = {"uint32", "uint64", "fast_uint32"};

	if (argc >= 5) {
		for (dt = 0; dt < 5; dt++)
			if (dtypes[dt] == argv[1]) break;
		for (it = 0; it < 3; it++)
			if (itypes[it] == argv[2]) break;
		std::istringstream is_n(argv[3]);
		is_n >> n;
		std::istringstream is_m(argv[4]);
		is_m >> m;
  	    if (argc == 6) {
  	    	std::istringstream is_nthreads(argv[5]);
  	    	is_nthreads >> nthreads;
  	    }
	}
	if (argc != 5 && argc != 6) {
		usage(argv[0]);
		std::exit(-1);
	}
	if (dt < 0 || dt > 4 || it < 0 || it > 2) {
		usage(argv[0]);
		std::exit(-1);
	}

    std::cout << "n = " << n << ", m = " << m << ", nthreads = " 
              << nthreads << std::endl;
	if (dt == 0 && it == 0)
		run_it<std::uint32_t,std::uint32_t>(n, m, nthreads);
	else if (dt == 0 && it == 1)
		run_it<std::uint32_t,std::uint64_t>(n, m, nthreads);
	else if (dt == 0 && it == 2)
		run_it<std::uint32_t,std::uint_fast32_t>(n, m, nthreads);

	else if (dt == 1 && it == 0)
		run_it<float,std::uint32_t>(n, m, nthreads);
	else if (dt == 1 && it == 1)
		run_it<float,std::uint64_t>(n, m, nthreads);
	else if (dt == 1 && it == 2)
		run_it<float,std::uint_fast32_t>(n, m, nthreads);

	else if (dt == 2 && it == 0)
		run_it<std::uint64_t,std::uint32_t>(n, m, nthreads);
	else if (dt == 2 && it == 1)
		run_it<std::uint64_t,std::uint64_t>(n, m, nthreads);
	else if (dt == 2 && it == 2)
		run_it<std::uint64_t,std::uint_fast32_t>(n, m, nthreads);

	else if (dt == 3 && it == 0)
		run_it<double,std::uint32_t>(n, m, nthreads);
	else if (dt == 3 && it == 1)
		run_it<double,std::uint64_t>(n, m, nthreads);
	else if (dt == 3 && it == 2)
		run_it<double,std::uint_fast32_t>(n, m, nthreads);

	else if (dt == 4 && it == 0)
		run_it<fake_number<std::uint32_t,16>,std::uint32_t>(n, m, nthreads);
	else if (dt == 4 && it == 1)
		run_it<fake_number<std::uint32_t,16>,std::uint64_t>(n, m, nthreads);
	else if (dt == 4 && it == 2)
		run_it<fake_number<std::uint32_t,16>,std::uint_fast32_t>(n, m, nthreads);

	return 0;
}



