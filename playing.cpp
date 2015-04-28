


#include<iostream>
#include<bitset>
#include<sstream>
#include<algorithm>

#include<cstdlib>

using namespace std;

string bin_fmt(int x, int d) {
	bitset<8> bsx(x);
	ostringstream os;
	os << bsx;
	return os.str().substr(8-d,d);
}

string bin_fmt_r(int x, int d) {
	string s = bin_fmt(x, d);
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

	// walk down the left roof from the root
	/* 
	 * replacing this code
     * ----------------snip--------------
	while (label > 0) { 
		parity |= (label & 1) << depth;
		label >>= 1;	
		depth++;
	}
	* ----------------snip--------------
	* with the following code:
    */
	parity = label;
	depth = w - __builtin_clz(label);
	label = 0;

    cout << "label = " << label << endl;
	cout << "depth = " << depth << endl;
	cout << "path = " << bin_fmt_r(path, depth) << endl;
	cout << "parity = " << bin_fmt_r(parity, depth) << endl;

	for (int i = 0; i <= h; i++)  {
		cout << "=======" << endl;
		int t1s = __builtin_clz(~(path<<(w-depth)));
		cout << "trailing ones = " << t1s << endl;

		// walk up the right roof of the current subtree
		cout << "Walking up right roof of height " << t1s << endl;
		int parity0 = parity;
		int depth0 = depth;
		int label0 = label;
		for (int j = 0; j < t1s; j++) {
			depth--;
			path &= ~(1<<depth);
			label <<= 1;
			cout << "  label = " << label << " (" << bin_fmt(label, 8) 
			     << ") [left shift] j = " << j << endl;
			label += 1<<((~(parity>>depth))&1);
			cout << "  label = " << label << " (" << bin_fmt(label, 8) 
			     << ") [add] j = " << j << endl;
			parity &= ~(1<<depth);
		}
		cout << "  label = " << label << " (" << bin_fmt(label, 8) 
		     << ")" << endl;

		// convert to this:
		int mask = (1<<depth0)-1;
		cout << " mask = " << bin_fmt(mask, 8) << endl;
		depth0 -= t1s;
		int plus_ones = parity0 >> depth0;
		cout << "+1's = " << bin_fmt(plus_ones, 8);
		int plus_twos = ((~parity0 & mask) >> depth0) << 1;
		cout << " +2's = " << bin_fmt(plus_twos, 8) << endl;
		label0 += plus_ones + plus_twos;
		cout << "left-thigh label = " << label0 << endl;
		parity0 &= (1<<depth0)-1;
		if (parity0 != parity || depth0 != depth || label0 != label) {
			cerr << "!!!!!!!!!!!!!!!!!Fuck!!!!!!!!!!!!!!!!!!!" << endl;
		}

		// now step up to the crotch 
		// depth--; (C) redundant with D 
		//           (but use depth -1 in next two formulas)
		label = (label << 1) | ((parity >> (depth-1)) & 1);
		// parity &= ~(1<<depth);  // (A) redundant with (B)
		// path &= ~(1<<depth); // not needed
		cout << "crotch label = " << label << endl;

		// step down to right child of crotch
		path |= 1 << (depth-1);
		// parity |= (label&1) << depth; // (B) redundant with (A)
		label = (label-1)>>1;
		// depth++; (D) redundant with (C)

		// walk down the left roof
		/* Replacing this code
		 * --------------------snip--------------------
		while (label > 0) { 
			parity |= (label&1) << depth;
			label >>= 1;	
			depth++;
		}
		 * --------------------snip--------------------
		 * with the following code:
		 */
		cout << "label0 = " << label << endl;
		// FIXME: clz is undefined if label==0, think of something better
		int down = label == 0 ? 0 : w - __builtin_clz(label);
		cout << "down = " << down << endl;
		parity |= label << depth;
		depth += down;
		label = 0;

	    cout << "label = " << label << endl;
		cout << "depth = " << depth << endl;
		cout << "path = " << bin_fmt_r(path, depth) << endl;
		cout << "parity = " << bin_fmt_r(parity, depth) << endl;
	}

	return 0;
}
