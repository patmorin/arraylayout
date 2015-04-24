
#include<cstdlib>
#include<cinttypes>

#include<iostream>
#include<fstream>
#include<chrono>

typedef int32_t data_t;
typedef int32_t index_t;
typedef uint32_t seq_t;

typedef struct {
  data_t x;
  // index_t left, right;  // TODO: eliminate these
} entry;


// An implementation of binary search on a sorted array
data_t binary_successor(data_t x, entry* a, index_t n) {
        data_t ans = -1;
        while (n > 0) {
                index_t m = n/2;
                if (x < a[m].x) {
                        ans = a[m].x;
                        n = m; // recurse on data[0,...,m-1]
                } else if (x > a[m].x) {
                        a += m+1; // recurse on data[m+1,...n]
                        n -= m+1;
                } else {
                        return a[m].x;
                }
        }
        return ans;
}


// An implementation of search in a VEB layout array
//index_t veb_successor(data_t x, entry *a) {
//  index_t i = 0, j = -1;
//  
//  while (i >= 0) {
//    if (x < a[i].x) {
//      j = i;
//      i = a[i].left;
//    } else if (x > a[i].x) {
//      i = a[i].right;
//    } else {
//      return i;
//    }
//  }
//  return j;
//}

void sequencer(int h, seq_t s[][2], size_t d) {
  if (h == 0) return;
  int h0 = h/2;
  int h1 = h-h0-1;
  sequencer(h0, s, d);
  s[d+h0][0] = h0;
  s[d+h0][1] = h1;
  sequencer(h1, s, d+h0+1);
}

// An implementation of search in a VEB layout array
index_t veb_successor2(data_t x, entry *a, index_t h, seq_t s[][2]) {
  index_t rtl[32];

  // data_t y = -1;
  index_t j = -1;
  index_t i = 0;
  index_t p = 0;
  for (int d = 0; d <= h; d++) {
    rtl[d] = i;
    if (x < a[i].x) {
      // std::cout << x << " < " << a[i].x << std::endl;
      p <<= 1;
      j = i;
    } else if (x > a[i].x) {
      // std::cout << x << " > " << a[i].x << std::endl;
      p = (p << 1) + 1;
    } else {
      // std::cout << x << " = " << a[i].x << "done!" << std::endl;
      return i;
    }
    index_t m = (1 << (s[d][0]+1))-1;
    i = rtl[d-s[d][0]] + (2<<s[d][0])-1 + (p&m)*((2<<s[d][1])-1);
  }
  return j;
}

void warm_up(entry* a, int n) {
  srand(0);
  data_t sum = 0;
  for (index_t i = 0; i < 5*n; i++) {
    sum += a[rand()%n].x; 
  }
  std::cout << "warmup sum = " << sum << std::endl;
}


int main(int argc, char *argv[])
{
  index_t h, n;

  std::cout << "Reading input...";
  std::cout.flush();

  // Read the VEB array from our python program
  std::ifstream f("veb.dat");
  f >> h >> n;
  entry *a = new entry[n]; 
  for (index_t i = 0; i < n; i++) {
    index_t dummy;
    f >> a[i].x >> dummy >> dummy;
    // if (a[i].left > 0) a[i].left += i;
    // if (a[i].right > 0) a[i].right += i;
  }
  f.close();
  std::cout << "done" << std::endl;
  std::cout << "h = " << h << ", n = " << n << std::endl;

  index_t m = 5*n;

  // Do some search tests on the VEB array
  warm_up(a, n);
  srand(0);
  seq_t s[32][2];
  sequencer(h, s, 0);
  s[h][0] = 0;
  s[h][1] = 0;
  for (int i = 0; i < h; i++) {
      std::cout << "(" << ((int)s[i][0]) << "," << ((int)s[i][1]) << ")";
  }
  std::cout << std::endl;
  std::cout << "Performing " << m << " VEB searches...";
  std::cout.flush();
  auto start = std::chrono::high_resolution_clock::now();
  data_t sum = 0; // to keep things from getting optimized out
  for (index_t i = 0; i < m; i++) {
    data_t x = rand() % (2*n);
    index_t j = veb_successor2(x, a, h, s);
    data_t y = (j < 0) ? -1 : a[j].x;
    sum += y;
  }
  auto stop = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = stop - start;
  std::cout << "done in " << elapsed.count() << "s (sum = " << sum << ")" << std::endl;

  // Do some search tests on the VEB array
  warm_up(a, n);
  srand(0);
  std::cout << "Performing " << m << " VEB2 searches...";
  std::cout.flush();
  start = std::chrono::high_resolution_clock::now();
  sum = 0; // to keep things from getting optimized out
  for (index_t i = 0; i < m; i++) {
    data_t x = rand() % (2*n);
    index_t j = veb_successor2(x, a, h, s);
    data_t y = (j < 0) ? -1 : a[j].x;
    sum += y;
  }
  stop = std::chrono::high_resolution_clock::now();
  elapsed = stop - start;
  std::cout << "done in " << elapsed.count() << "s (sum = " << sum << ")" << std::endl;



  // Now setup the array up as a sorted array
  for (index_t i = 0; i < n; i++) {
    a[i].x = 2*i;
    //a[i].left = -1;
    //a[i].right = -1;
  }

  // Do some search tests on the sorted array
  warm_up(a, n);
  srand(0);
  std::cout << "Performing " << m << " binary searches...";
  std::cout.flush();
  start = std::chrono::high_resolution_clock::now();
  sum = 0; // to keep things from getting optimized out
  for (index_t i = 0; i < m; i++) {
    data_t x = rand() % (2*n);
    data_t y = binary_successor(x, a, n);
    sum += y;
  }
  stop = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed2 = stop - start;
  std::cout << "done in " << elapsed2.count() << "s (sum = " << sum << ")" << std::endl;

  std::cout << "Slowdown factor = " << elapsed2.count()/elapsed.count() << std::endl;

  //delete[] a;
}



