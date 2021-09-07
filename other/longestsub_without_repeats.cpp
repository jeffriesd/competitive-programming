// problem: https://leetcode.com/problems/longest-substring-without-repeating-characters/


#include <vector>
#include <string>


class Solution {
  public:
    bool contains(vector<char> v, char target)
    {
      for (int i = 0; i < v.size(); i++)
      {
        if (target == v[i])
        {
          return true;
        }
      }
      return false;
    }

    int uniqueSubLen(string sub)
    {
      vector<char> u(0);
      int len = 0;

      const char * c = sub.c_str();
      while (! contains(u, *c) && *c)
      {
        len++;
        u.push_back(*c);
        c++;
      }
      return len;
    }

    int lengthOfLongestSubstring(string s) {
      int length = 0;
      int maxLength = 0;

      for (int i = 0; i < s.size(); i++)
      {
        string sub = s.substr(i, s.size());
        //get max length for substring s[i:]
        length = uniqueSubLen(sub);

        maxLength = length > maxLength ? length : maxLength;
      }
      return maxLength;
    }
};
