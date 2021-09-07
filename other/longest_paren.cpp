// problem: https://leetcode.com/problems/longest-valid-parentheses/



class Solution {
  public:
    int longestValidParentheses(string s) {
      if (s == "") return 0;
      if (s.length() < 2) return 0;

      stack<int> unrs; 
      vector<int> sol (s.length(), 0);

      if (s[s.length() - 1] == ')') 
        unrs.push(s.length() - 1);

      int u;
      for (int i = s.length() - 2; i >= 0; i--) {
        if (s[i] == '(') {
          if (! unrs.empty()) {
            u = unrs.top();
            unrs.pop();
            sol[i] = u - i + 1 + 
              (u < s.length() - 1 ? sol[u+1] : 0);
          }
        }

        if (s[i] == ')') {
          unrs.push(i); 
          sol[i] = 0;
        }
      }

      return *max_element(sol.begin(), sol.end());
    }
};
