/*
ID: jeffrie1
LANG: C++
TASK: job
*/

#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

int main() {
  ofstream fout ("job.out");
  ifstream fin ("job.in");

  int N, M1, M2;

  fin >> N >> M1 >> M2;

  vi A (M1, 0);
  vi B (M2, 0);

  for (int i = 0; i < M1; i++)
    fin >> A[i];

  for (int i = 0; i < M2; i++)
    fin >> B[i];

  sort(begin(A), end(A));
  sort(begin(B), end(B));

  // greedily do A stage
  // using priority queue with elements
  // (x, k) where x is cost of machine 
  // and k is original cost of machine
  // 
  // we can model putting a job into machine of cost k
  // as exchanging the machine for another machine
  // of cost 2k which is immediately available 
  vector<pair<int, pi>> Apair;
  for (int i = 0; i < M1; i++) {
    Apair.push_back({A[i], {A[i], i}});
  }

  vector<pair<int, pi>> Bpair;
  for (int i = 0; i < M2; i++) {
    Bpair.push_back({B[i], {B[i], i}});
  }

 

  auto comp = [](pair<int, pi> &p1, pair<int, pi> &p2) {
    // x > y gives minheap
    // x < y gives maxheap
    //
    return p1 > p2;
    //
    // false, p1 goes first 
    // int x1, y1, z1;
    // x1 = p1.first;
    // tie(y1, z1) = p1.second;
    // int x2, y2, z2;
    // x2 = p2.first;
    // tie(y2, z2) = p2.second;

    // return x1 > x2 && y1 > y2 && z1 > z2;
  };

  typedef priority_queue<pair<int, pi>, vector<pair<int, pi>>, decltype(comp)> minpq ;
  // need triple so there can be multiple copies 
  // priority_queue<pair<int, pi>> pa (begin(Apair), end(Apair));
  minpq pa(comp); // (begin(Apair), end(Apair));
  vi finishtimes;

  // put A machines in priority queue
  for (auto p : Apair)
    pa.push(p);

  // compute finish times for 
  // A operation
  pi p;
  int t, k, j;
  for (int i = 0; i < N; i++) {
    tie(t, p) = pa.top();
    tie(k, j) = p;
    pa.pop();

    finishtimes.push_back(t);
    pa.push({t+k, {k, j}});
  }
  

  // B stage is basically A but in reverse
  // we can greedily assign machine
  // starting with last job to finish A stage
  minpq pb(comp);
  vi bfinishtimes;

  for (auto p : Bpair)
    pb.push(p);

  for (int i = 0; i < N ; i++) {
    tie(t, p) = pb.top();
    tie(k, j) = p;
    pb.pop();

    bfinishtimes.push_back(t);
    pb.push({t+k, {k, j}});
  }

  reverse(begin(bfinishtimes), end(bfinishtimes));

  int maxatime = 0;
  int maxbtime = 0;
  for (int i = 0; i < N; i++) {
    maxatime = max(maxatime, finishtimes[i]);
    maxbtime = max(maxbtime, finishtimes[i] + bfinishtimes[i]);
  }

  fout << maxatime << " " << maxbtime << endl;

  return 0;
}
