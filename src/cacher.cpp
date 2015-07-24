/*
 * cacher.cpp
 *
 *  Created on: 2015-04-24
 *      Author: morin
 */
#include <chrono>
#include <random>
#include <iostream>

int main(int argc, char *argv[]) {
	for (double dbytes = 16; dbytes <= (1<<28); dbytes *= 1.2589254117941673) {
        int nbytes = (int)dbytes;
    	int n = nbytes/sizeof(int);
		int m = 10000000;
    	int *a = new int[n];
    	for (int i = 0; i < n; i++) 
    		a[i] = i;
    
    	std::minstd_rand re(23433);
    	std::uniform_int_distribution<int> ui(0, n-1);
    
    	auto start = std::chrono::high_resolution_clock::now();
    	int sum = 0;
    	for (int i = 0; i < m; i++) {
    		sum += a[ui(re)];
    	}
    	auto stop = std::chrono::high_resolution_clock::now();
    	std::chrono::duration<double> elapsed = stop - start;
    	delete[] a;
		std::cout << nbytes << " " << elapsed.count() << " " 
                  << sum << std::endl; 
   } 
   return 0;
}
