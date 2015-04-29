/*
 * main.cpp
 *
 *  Created on: 2015-04-24
 *      Author: morin
 */

#include <chrono>
#include <random>
#include "veb_array.h"
#include "bfs_array.h"

// #include <cpucounters.h>

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


// An implementation of binary search on a sorted array
template<class T, class I>
I binary_search(const T &x, const T *a, I n) {
	I lo = 0;
	I hi = n;
	while (lo < hi) {
		I m = (lo + hi) / 2;
		if (x < a[m]) {
			hi = m;
		} else if (x > a[m]) {
			lo = m+1;
		} else {
			return m;
		}
	}
	return hi;
}

template<class T, class I>
void run_tests(I n) {
	cout << "=======================================================" << endl;
	cout << "Running tests with " << 8*sizeof(T) << "-bit data and "
			<< 8*sizeof(I) << "-bit indices" << endl;

	//std::random_device rd;   -- using this causes a memory leak
	auto seed = 23433; // used a fixed seed instead of random_device
	std::mt19937 re;
	std::uniform_int_distribution<int> ui(0, 2*n+1);

	cout << "Allocating and filling sorted array...";
	cout.flush();
	auto start = std::chrono::high_resolution_clock::now();
	T *a = new T[n];
	for (I i = 0; i < n; i++)
		a[i] = 2*(i+1);
	auto stop =  std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = stop - start;
	cout << "done (" << elapsed.count() << "s)" << endl;

	cout << "Building VEB array...";
	cout.flush();
	start = std::chrono::high_resolution_clock::now();
	veb_array<T,I> va(a, n);
	stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	cout << "done (" << elapsed.count() << "s)" << endl;

	int m = 10000000;
	std::cout << "Performing " << m << " VEB searches...";
	std::cout.flush();
	re.seed(seed);
	start = std::chrono::high_resolution_clock::now();
	int sum = 0;
	for (int i = 0; i < m; i++) {
		T x = ui(re);
		I j = va.search(x);
		sum += (j < n) ? (int)va.get_data(j) : -1;
	}
	stop = std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done in " << elapsed.count() << "s (sum = " << sum << ")"
			<< std::endl;


	cout << "Building BFS array...";
	cout.flush();
	start = std::chrono::high_resolution_clock::now();
	bfs_array<T,I> ba(a, n);
	stop =  std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	cout << "done (" << elapsed.count() << "s)" << endl;

	std::cout << "Performing " << m << " BFS searches...";
	std::cout.flush();
	re.seed(seed);
	start = std::chrono::high_resolution_clock::now();
	sum = 0;
	for (int i = 0; i < m; i++) {
		T x = ui(re);
		I j = ba.search(x);
		sum += (j < n) ? (int)ba.get_data(j) : -1;
	}
	stop = std::chrono::high_resolution_clock::now();
	elapsed = stop - start;
	std::cout << "done in " << elapsed.count() << "s (sum = " << sum << ")"
			<< std::endl;


	std::cout << "Performing " << m << " binary searches...";
	std::cout.flush();
	re.seed(seed);
	start = std::chrono::high_resolution_clock::now();
	sum = 0;
	for (int i = 0; i < m; i++) {
		T x = ui(re);
		I j = binary_search<T,I>(x, a, n);
		sum += j < n ? (int)a[j] : -1;
	}
	stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed2 = stop - start;
	std::cout << "done in " << elapsed2.count() << "s (sum = " << sum << ")"
			<< std::endl;

	std::cout << "Slowdown factor = " << elapsed2.count()/elapsed.count()
			<< std::endl;

	delete[] a;
}

int main(int argc, char *argv[]) {
	int n = (argc > 1) ? atoi(argv[1]) : 52;

	run_tests<int,unsigned>(n);
	run_tests<long long int,unsigned>(n);
	run_tests<fake_int_128,unsigned>(n);
}



