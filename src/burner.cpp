#include <random>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	int n = (argc > 1) ? atoi(argv[1]) : 52;

	std::mt19937 re;
	std::uniform_int_distribution<int> ui(0, n-1);

	long long sum = 0;
	unsigned *a = new unsigned[n];
	for (unsigned i = 0; i < (unsigned)n; i++) {
		a[i] = i;
	}
	while (1 < 2) {
		unsigned i = ui(re);
		sum += a[i];
		if (sum == 0) {
			cout << "Jackpot!" << endl;
		}
	}
	delete[] a;
	return 0;
}
