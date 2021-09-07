/*
ID: jeffrie1
LANG: C++
TASK: humble
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using ull = unsigned long long;
using vll = vector<unsigned long long>;
using vb = vector<bool>;
using si = set<int>;


vll humbles;

int main() {
  ofstream fout ("humble.out");
  ifstream fin ("humble.in");

  int K, N;
  fin >> K >> N;
  vll nums(K, 0);
  for (int i = 0; i < K; i++) 
    fin >> nums[i];
  sort(begin(nums), end(nums));

  // solution: generate first N humble numbers over S
  // in order. essentially each member of S (nums) has its own
  // queue, all initially filled with 1. 
  //
  //  queue for 2: [ 1 ] 
  //  queue for 3: [ 1 ] 
  //  queue for 5: [ 1 ] 
  //
  // to find the next humble number, find the minimum product
  // nums[i] * front(queue[i]), pop the first element of queue[i]
  // and then add the product to the back of each queue
  //
  //  pop (2, 1) 
  //  queue for 2: [ 2 ] 
  //  queue for 3: [ 1 , 2 ] 
  //  queue for 5: [ 1 , 2 ] 
  //
  //  pop (3, 1)
  //  queue for 2: [ 2 , 3 ] 
  //  queue for 3: [ 2 , 3 ] 
  //  queue for 5: [ 1 , 2 , 3 ] 
  //
  //  pop (2, 2)
  //  queue for 2: [ 3 , 4 ] 
  //  queue for 3: [ 2 , 3 , 4 ] 
  //  queue for 5: [ 1 , 2 , 3 , 4 ] 
  //
  //  Since the numbers in each queue will be the same,
  //  we can just store our queue as an array (humbles) and 
  //  keep track of the front index for each S_i
  //
  //  we can find the minimum quickly using single priority queue
  //  whose elements are (S_i, j) where S_i is an element of nums
  //  and j is an index into humbles. The priority queue is a min
  //  heap ordered on (S_i * humbles[j]). 

  humbles.push_back(1);

  // heap entries are (n_i, j) where n_i is some prime in nums
  // and j is an index into a list of humble numbers 
  auto comp = [](pair<ull, int> &p1, pair<ull, int> &p2) { 
                  // when false, place p1 first
                  // when true, place p2 first

                  // printf("i1 = %d, i2 = %d, humbles size = %d\n", p1.second, p2.second, humbles.size());
                  // place p2 first if product(p2) is < 
                  // product(p1)
                  if (p1.second < 0 || p1.second >= humbles.size()
                      || p2.second < 0 || p2.second >= humbles.size()) {
                    cout << "bounds error " << endl;
                    exit(1);
                  }
                  ull prod1 = p1.first * humbles[p1.second];
                  ull prod2 = p2.first * humbles[p2.second];
                  return prod1 > prod2;
                };


  // must use decltype() and pass comp to constructor
  typedef priority_queue<pair<ull, int>, vector<pair<ull, int>>, decltype(comp)> pq_t;

  pq_t * pq = new pq_t (comp);
  for (int x : nums) 
    pq->push({x, 0});

  set<ull> allNums;

  ull x;
  int ind;
  ull prod;
  while (humbles.size() <= N) {
    tie(x, ind) = pq->top();
    pq->pop();

    prod = x * humbles[ind];
    // check for overflow
    if (prod > (unsigned int)(1 << 31))  
      break;

    if (allNums.find(prod) == allNums.end()) {
      humbles.push_back(prod);
      allNums.insert(prod);
    }

    // move x to next index
    pq->push({x, ind+1});
  }

  fout << humbles[humbles.size() - 1] << endl;

  return 0;
}
