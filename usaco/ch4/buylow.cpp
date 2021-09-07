/*
ID: jeffrie1
LANG: C++
TASK: buylow
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

ofstream fout ("buylow.out");
ifstream fin ("buylow.in");


vvi parents; 
vi S, prices;

#define MAXDIGS 99
#define BASE 1000

class BigInt {
  // int MAXDIGS = 999;

  // digs[0] is x0 
  // digs[1] is x1
  //
  // and the number is
  //
  // x0 + BASE * x1 + BASE^2 * x2 ... 
  // vi digs(50, 0);
  vi digs;

  public:
  BigInt(int m) {
    // build bigint from n 
    //
    for (int i = 0; i < MAXDIGS; i++)
      digs.push_back(0);
    long long n = (long long)m;

    long long b = 1;
    int bi = 0;

    
    // find largest non-zero digit
    while (b * BASE < n) {
      b *= BASE;
      bi++;
    }

    // fill out bi^th digit 
    for (; bi >= 0; bi--) {

      long long dig = n / b;
      digs[bi] = dig;
      // take off numdigs * b
      n -= dig * b;

      b /= BASE;
    }
  }

  int mostSig() {
    // return the (position of) 
    // the most significant digit 
    int bi;
    for (bi = MAXDIGS-1; digs[bi] == 0 && bi > 0; bi--)
      ;
    return bi;
  }

  void add(BigInt big) {
    // add another BigInt to myself

    int b = 1;

    int carry = 0;
    for (int i = 0; i < MAXDIGS; i++) {
      int xi = digs[i];
      int yi = big.digs[i];

      int sum = xi + yi + carry;
      int di = sum % BASE;

      digs[i] = di;

      carry = sum / BASE;
    }
  }

  void printDec() {
    // print decimal 
    //
    char s[MAXDIGS * 4];
    // start at leftmost non-zero digit
    char * sp = s;
    for (int bi = mostSig(); bi >= 0; bi--) {
      int len; 
      if (bi == mostSig())
        len = sprintf(sp, "%d", digs[bi]);
      else
        len = sprintf(sp, "%03d", digs[bi]);
      sp += len;
    }

    fout << s ;
  }

  char * decString() {
    //
    char * s = new char[MAXDIGS * 4];
    // start at leftmost non-zero digit
    char * sp = s;
    for (int bi = mostSig(); bi >= 0; bi--) {
      // cout << width(3) << digs[bi]; 
      int len; 
      if (bi == mostSig())
        len = sprintf(sp, "%d", digs[bi]);
      else
        len = sprintf(sp, "%03d", digs[bi]);
      sp += len;
    }
    return s;
  }

  bool isZero() {
    return mostSig() == 0 && digs[0] == 0;
  }
};



vector<BigInt> P;

BigInt solve_partitions(vi);
BigInt numsequences(int );

BigInt solve_partitions(vi inds) {
  // inds - indices j s.t. prices[j] 
  //        is the same for every j
  //        (i.e. a partition) 

  unordered_map<int, unordered_set<int>> partitions;
  for (int j : inds) {
    for (int k : parents[j]) {

      int p = prices[k];

      if (partitions.find(p) == partitions.end()) {
        unordered_set<int> s;
        partitions.insert({p, s});
      }

      partitions[p].insert(k);
    }
  }

  BigInt ans(0);
  for (auto &p : partitions) {
    vi ind (p.second.begin(), p.second.end());
    if (p.second.size() == 1) {// single parent with a particular value
      ans.add(numsequences(ind[0]));
    }
    if (p.second.size() > 1) { 
      ans.add(solve_partitions(ind));
    }
    // cout << "ans = " << ans << endl;
  }
  if (ans.isZero()) 
    ans.add(BigInt(1));

  return ans;
}

BigInt numsequences(int j) {
  if (! P[j].isZero()) return P[j];

  unordered_map<int, vi> partitions;

  // partition parents based on value
  for (int k : parents[j]) {

    int p = prices[k];

    if (partitions.find(p) == partitions.end())
      partitions.insert({p, vi()});

    partitions[p].push_back(k);
  }

  BigInt ans(0);
  for (auto &p : partitions) {

    if (p.second.size() == 1) // single parent with a particular value
      // P should be defined for this index since
      // it is necessarily < j 
      ans.add(P[p.second[0]]);
    if (p.second.size() > 1) {
      ans.add(solve_partitions(p.second));
    }
  }

  if (ans.isZero()) {
    // printf("is Zero : %s\n", ans.decString());
    ans.add(BigInt(1));
  }


  P[j] = ans;
  return P[j];
}



int main() {


  int N; // number of days 

  fin >> N;

  int x;
  for (int i = 0; i < N; i++) {
    fin >> x;
    prices.push_back(x);
  }

  // append input sequence with -1
  // so max seq length is just in S[N]

  prices.push_back(-1);

  // problem: find length of longest decreasing
  // sequence and count the number of sequences
  // with this length
  //
  // S[i] = length of longest decreasing sequence
  //        ending at index i
  //
  // P[i] = number of distinct sequences of length
  //        S[i] ending at index i
  //
  // initialize for all i,
  // S[i] = 1 
  // P[i] = 0

  for (int i = 0; i < N+1; i++) {
    S.push_back(1);
    P.emplace_back(0);
  }
  P[0] = BigInt(1);

  parents.push_back(vi()); // first element has no parents

  for (int i = 1; i < N+1; i++) {
    // prices[i] can extend from j < i
    // s.t. prices[j] < prices[i]

    // find maximum length we can extend from 
    int maxsub = 0;
    vi inds; 
    for (int j = 0; j < i; j++) {
      if (prices[j] <= prices[i]) continue;
      maxsub = max(maxsub, S[j]);
    }
    S[i] = maxsub + 1;

    for (int j = 0; j < i; j++)
      if (prices[j] > prices[i] && S[j] == maxsub) 
        inds.push_back(j);

    parents.push_back(inds);
  }

  int maxlen = S[N] - 1; 

  for (int i = 0; i <= N; i++)
    numsequences(i);

  fout << S[N]-1 << " " ;
  P[N].printDec();
  fout << endl;
  return 0;
}
