// problem: https://open.kattis.com/problems/exam 

#include<bits/stdc++.h>
using namespace std;

int main() {
  int k;
  string me;
  string them;
  cin >> k;
  cin >> me; 
  cin >> them;

  int n = me.length();

  // nc = 3
  // Me: T T F F T 
  // th: T F T F T
  // ans = 5
  //
  // nc = 3
  // F T F F F 
  // T F T T T  
  // num disagree = 5
  // num disagree - nc = ans =2
  //
  // 6
  // n = 10
  // T T F T F F T F T F 
  // T T T T F F T T T T 
  // numd = 3
  // numa = 7
  //
  // they were right 6 times you agreed
  // they were wrong 1 time you agreed
  // and 3 times you disagreed (3 + 1 = 4 = 10 - 6)
  //
  // myc = n
  // if numagree > theirc
  //   myc -= (numagree - theirc)
  // else
  //  myc -= (theirc - numagree)
  //

  int numAgree = 0;
  for (int i = 0; i < n; i++) {
    if (me[i] == them[i]) numAgree++; 
  }
  int ans = n;
  if (numAgree > k)
    ans -= (numAgree - k);
  else
    ans -= (k - numAgree);

  cout << ans << endl;
  return 0;
}
