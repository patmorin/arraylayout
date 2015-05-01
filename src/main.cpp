/*
 * main.cpp
 *
 *  Created on: 2015-04-24
 *      Author: morin
 */

#include <chrono>
#include <random>
#include "veb_array.h"
#include "eytzinger_array.h"
#include "sorted_array.h"
#include "btree_array.h"

using namespace fbs;

class fake_int_128 {
	long long a[2];
public:
	fake_int_128() { };
	fake_int_128(int x) { a[0] = x; };
	bool operator<(const fake_int_128& x) const {
		return a[0] < x.a[0];
	};
	bool operator>(const fake_int_128& x) const {
		return a[0] > x.a[0];
	};
	bool operator==(const fake_int_128& x) const {
		return a[0] == x.a[0];
	};
	operator int() const { return (int)a[0]; };
	fake_int_128& operator+=(const fake_int_128& x) {
		a[0] += x.a[0];
		return *this;
	};
};


template<class Array, class T, class I>
void run_test1(T *a, I n, I m, const std::string &name) {

	auto seed = 23433;
	std::mt19937 re(23433);
	std::uniform_int_distribution<T> ui(0, 2*n+1);

	cout << "Building " << name << " array...";
	cout.flush();
	auto start = std::chrono::high_resolution_clock::now();
	Array aa(a, n);
	auto stop =  std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = stop - start;
	cout << "done (" << elapsed.count() << "s)" << endl;

	std::cout << "Performing " << m << " " << name << " searches...";
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

static const unsigned CACHE_LINE_WIDTH = 64;

template<class T, class I>
void run_tests(I n) {
	cout << "=======================================================" << endl;
	cout << "Running tests with " << 8*sizeof(T) << "-bit data and "
			<< 8*sizeof(I) << "-bit indices (n = " << n << ")" << endl;

	cout << "Allocating and filling sorted array...";
	cout.flush();
	auto start = std::chrono::high_resolution_clock::now();
	T *a = new T[n];
	for (I i = 0; i < n; i++)
		a[i] = 2*(i+1);
	auto stop =  std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = stop - start;
	cout << "done (" << elapsed.count() << "s)" << endl;

	int m = 10000000;
	for (int i = 0; i < 3; i++) {
		run_test1<sorted_array<T,I>,T,I>(a, n, m, "binary");
		run_test1<veb_array<T,I>,T,I>(a, n, m, "veb");
		run_test1<eytzinger_array<T,I>,T,I>(a, n, m, "eytzinger");
		const unsigned b = CACHE_LINE_WIDTH/sizeof(T);
		std::ostringstream s;
		s << (b+1) << "-tree";
		run_test1<btree_array<64/sizeof(T),T,I>,T,I>(a, n, m, s.str());
	}
}

//typedef unsigned long long index_t;
//typedef unsigned long long data_t;

typedef unsigned index_t;
typedef unsigned data_t;

int main(int argc, char *argv[]) {
	index_t n;
	if (argc == 2) {
		std::istringstream is(argv[1]);
		is >> n;
	} else {
		std::cerr << "Usage: " << argv[0] << " <n>" << std::endl;
		std::exit(-1);
	}
	std::cout << "n = " << n << std::endl;

	run_tests<data_t,index_t>(n);
	// run_tests<long long int,unsigned>(n);
	// run_tests<fake_int_128,unsigned>(n);
}



