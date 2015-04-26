/*
 * main.cpp
 *
 *  Created on: 2015-04-24
 *      Author: morin
 */

#include <chrono>
#include <random>
#include "veb_array.h"

// #include <cpucounters.h>


// An implementation of binary search on a sorted array
template<class T, class I>
I binary_successor(const T &x, const T *a, I n) {
	const T *a0 = a;
	const I n0 = n;
	const T *ans = NULL;
	while (n > 0) {
		I m = n/2;
		if (x < a[m]) {
			ans = &a[m];
			n = m; // recurse on data[0,...,m-1]
		} else if (x > a[m]) {
			a += m+1; // recurse on data[m+1,...n]
			n -= m+1;
		} else {
			return &a[m] - a0;
		}
	}
	return ans == NULL ? n0 : ans-a0;
}

// An implementation of binary search on a sorted array
template<class T, class I>
I binary_successor2(const T &x, const T *a, I n) {
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


int main(int argc, char *argv[]) {
	int n = (argc > 1) ? atoi(argv[1]) : 52;

	//std::random_device rd;   -- using this causes a memory leak
        auto seed = 23433; // rd();
	std::mt19937 re;
	std::uniform_int_distribution<int> ui(0, 2*n+1);

	cout << "Allocating and filling sorted array...";
	cout.flush();
	auto start = std::chrono::high_resolution_clock::now();
	int *a = new int[n];
	for (int i = 0; i < n; i++)
		a[i] = 2*(i+1);
    auto stop =  std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = stop - start;
    cout << "done (" << elapsed.count() << "s)" << endl;

	cout << "Building VEB array...";
	cout.flush();
	start = std::chrono::high_resolution_clock::now();
    veb_array<int,int> va(a, n);
    stop =  std::chrono::high_resolution_clock::now();
    elapsed = stop - start;
    cout << "done (" << elapsed.count() << "s)" << endl;

    re.seed(seed);
    int m = 30000000;
    // m = n > m ? n : m;
    std::cout << "Performing " << m << " VEB searches...";
    std::cout.flush();
    start = std::chrono::high_resolution_clock::now();
    int sum = 0; 
    for (int i = 0; i < m; i++) {
      int x = ui(re); 
      int j = va.search(x);
      sum += (j < n) ? va.get_data(j) : -1;
    }
    stop = std::chrono::high_resolution_clock::now();
    elapsed = stop - start;
    std::cout << "done in " << elapsed.count() << "s (sum = " << sum << ")" << std::endl;

/*
    re.seed(seed);
    std::cout << "Performing " << m << " binary searches...";
    std::cout.flush();
    start = std::chrono::high_resolution_clock::now();
    sum = 0; 
    for (int i = 0; i < m; i++) {
      int x = ui(re); 
      int j = binary_successor2(x, a, n);
      sum += j < n ? a[j] : -1;
    }
    stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed2 = stop - start;
    std::cout << "done in " << elapsed2.count() << "s (sum = " << sum << ")" << std::endl;

    std::cout << "Slowdown factor = " << elapsed2.count()/elapsed.count() << std::endl;
*/
    delete[] a;
}



