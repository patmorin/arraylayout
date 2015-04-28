


#include<iostream>
#include<bitset>
#include<strstream>
#include<algorithm>
#include<cstdlib>

using namespace std;

string bin_fmt(int x, int d) {
	bitset<8> bsx(x);
	ostrstream os;
	os << bsx;
	string s = std::string(os.str()).substr(8-d,d);
	reverse(s.begin(), s.end());
	return s;
}

int main(int argc, char **argv) {
	
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <h>" << endl;
		exit(-1);
	}

	int h = atoi(argv[1]);
      
	int w = 8*sizeof(h); 
	int q = w-__builtin_clz(h); // number of bits in h
	cout << "q = " << q << endl;

	// make the initial path
	int path = 0;     // an encoding of the root-to-leaf path
	int depth = 0;    // the depth of the root-to-leaf path
	int parity = 0;   // the parities of the labels on the r-t-l path
	int label = h;
	while (label > 0) { 
		parity |= (label & 1) << depth;
		label >>= 1;	
		depth++;
	}
    cout << "label = " << label << endl;
	cout << "depth = " << depth << endl;
	cout << "path = " << bin_fmt(path, depth) << endl;
	cout << "parity = " << bin_fmt(parity, depth) << endl;

	for (int i = 0; i <= h; i++)  {
		cout << "=======" << endl;
		int t1s = __builtin_clz(~(path<<(w-depth)));
		cout << "trailing ones = " << t1s << endl;

		// walk up the right roof ot the current subtree
		for (int j = 0; j < t1s; j++) {
			depth--;
			path &= ~(1<<depth);
			label <<= 1;
			label += 1<<((~(parity>>depth))&1);
			parity &= ~(1<<depth);
		}

		// now step up to the crotch 
		depth--;
		label <<= 1;
		label += (parity>>depth)&1;
		path &= ~(1<<depth);
		parity &= ~(1<<depth);
		cout << "crotch label = " << label << endl;

		// step down to right child of crotch
		path |= 1 << depth;
		parity |= (label&1) << depth;
		label = (label-1)>>1;
		depth++;

		// walk down the left roof
		while (label > 0) { 
			parity |= (label&1) << depth;
			label >>= 1;	
			depth++;
		}
	    cout << "label = " << label << endl;
		cout << "depth = " << depth << endl;
		cout << "path = " << bin_fmt(path, depth) << endl;
		cout << "parity = " << bin_fmt(parity, depth) << endl;
	}

	return 0;
}
