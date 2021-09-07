// problem: https://leetcode.com/problems/maximum-product-subarray/

class Solution {
  public:
    int maxProduct(vector<int>& nums) {
      vector<int> maxx (nums.size());
      vector<int> minn (nums.size());

      maxx[0] = nums[0];
      minn[0] = nums[0];
      int n;
      for (int i = 1; i < nums.size(); i++) {
        n = nums[i];
        maxx[i] = max(n, max(maxx[i-1] * n, minn[i-1] * n));
        minn[i] = min(n, min(maxx[i-1] * n, minn[i-1] * n));
      }

      int ans = maxx[0];
      for (int x : maxx)
        ans = max(x, ans);
      return ans;

    }
};
