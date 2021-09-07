// problem: https://leetcode.com/problems/maximum-subarray/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int> sol (nums.size());
        sol[0] = nums[0];
        for (int i = 1; i < nums.size(); i++)
            sol[i] = max(sol[i-1] + nums[i], nums[i]);
        int ans = sol[nums.size()-1];
        for (int x : sol)
            ans = max(ans, x);
        return ans;
    }
};
