#include <chrono>
#include <random>
#include <algorithm>
#include <iostream>

using namespace std;

std::chrono::duration<double> burn_it(int nbytes, int m) {
	cout << "Allocating and filling" << endl;
	int n = nbytes/sizeof(int);
	int *a = new int[n];
	for (int i = 0; i < n; i++) 
		a[i] = i;

	std::minstd_rand re(23433);
	std::uniform_int_distribution<int> ui(0, n-1);

	std::cout << "Performing random accesses" << std::endl;
	auto start = std::chrono::high_resolution_clock::now();
	int sum = 0;
	for (int i = 0; i < m; i++) {
		sum += a[ui(re)];
	}
	auto stop = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = stop - start;
	delete[] a;
	std::cout << "Done" << std::endl;
	std::cout << sum << std::endl;
	return elapsed;
}

int main(int argc, char *argv[]) {
	int n0, n1;

	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <cache size (KB)>" << endl;
		std::exit(0);
	}
	int n = atoi(argv[1]) * 1024;

	cout << "Using cache size " << n << endl;

	std::chrono::duration<double> t1 = burn_it(n, 50*n);
	std::chrono::duration<double> t2 = burn_it(20*n, 50*n);

	cout << "Estimated cache speedup " << (t2.count()/t1.count()) << endl;
	return 0;
}
