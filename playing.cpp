


#include<iostream>
#include<bitset>

using namespace std;

int main(void) {

	int h = 13;
	int base_h = h;
	int px = 0;
       
	int q = (8*sizeof(h))-__builtin_clz(h); // number of bits in h
	cout << "q = " << q << endl;
	for (int d = 0; d <= base_h; d++) {

		std::bitset<8> bspx(px);
		cout << "px = " << bspx << endl;

		// number of trailing ones in the path
		int t1s = __builtin_ctz(~px);  
		cout << "trailing ones = " << t1s << endl;

		// The path to the crotch eats up the lowest-order z bits
		int z = q-t1s-1;

		// the label at the crotch of the current step
		int label = h >> z;
		cout << "crotch label = " << label 
			<< " is " << ((label&1)? "odd" : "even") << endl;

		// the label also gives us the labels of its two children
		int h0 = label >> 1;
		int h1 = h0 - (~label&1);
		cout << "h0 = " << h0 << ", h1 = " << h1 << endl;

		// on the way down from the crotch, we messed up the high-order
		// t1s bits of h --- restore them now
   
        // mask looks like 1111111110000
		//                    |--------|
		//                        q
		//                    |---||---|
		//                     t1s   z
		int mask = ~((2 << z)-1);  
		std::bitset<8> bspmask(mask);
		cout << "mask = " << bspmask << endl;
		h = (base_h & mask) | (h & ~mask);
		cout << "restored h = " << h << endl;

		// if the label was odd we want to (effectively) subtract 2 from it
		int sub = (~label&1)<<(z+1);
		cout << "sub = " << sub << endl;
		h -= sub;
		cout << "new h = " << h << endl;

		cout << "======" << endl;
		px++;
		if (label == 2) px++;
	}
	return 0;
}
