// problem: https://leetcode.com/problems/palindrome-number/

class Solution {
  public:

    int digit(int n, int k)
    {
      return (n / ((int)pow(10, k)) % 10);
    }


    bool isPalindrome(int n) {
      if (n < 0)
        return false;

      int numDigits = 0;
      for (int i = n; i > 0; i /= 10)
      {
        numDigits++;
      }

      for (int i = 0; i < numDigits / 2; i++)
      {
        // check if ith digit = n-ith digit
        if (digit(n, i) != digit(n, numDigits - 1 - i))
          return false;
      }
      return true;

    }
};
